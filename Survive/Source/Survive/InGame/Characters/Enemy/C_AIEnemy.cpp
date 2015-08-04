#include "Survive.h"
#include "C_AIEnemy.h"
#include "AI/Navigation/NavigationPath.h"

UC_AIEnemy::UC_AIEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_AIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	enemy = Cast<ASEnemy>(GetOwner());
	TArray<UC_CombatEnemy*> combatEnemyArray;
	enemy->GetComponents(combatEnemyArray); combatEnemy = combatEnemyArray[0];

	player = Cast<ASPlayer>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
}

void UC_AIEnemy::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//When the enemy can't reach the player, this means he has a buildable in front of him
	if (ExistsValidPathToPlayer())
	{
		GEngine->AddOnScreenDebugMessage(125, 1.0f, FColor::Red, TEXT("SIMPLE MOVE!"));
		UNavigationSystem::SimpleMoveToLocation(enemy->GetController(), player->GetActorLocation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(125, 1.0f, FColor::Red, TEXT("STRAAAAAAAAAAAIIIGHT!"));

		//Move in a straight line(directly) to the player. Notify the UC_CombatEnemy that the enemy is not finding the
		//right path, so he can break the buildables in the middle.
		FVector dir = player->GetActorLocation() - enemy->GetActorLocation(); dir.Normalize();
		enemy->AddMovementInput(dir);

		combatEnemy->OnTickWithoutAValidPathToPlayer();
	}
}

//The IsValid() function from NavigationPath doesn't work for me, so the way I have to know if the player is reachable,
//is to check if the last point on the path is very very close to the player. If it is, then it's reachable. If not, then
//it is not reachable
//This problem comes up because even if the enemy can't reach the player, the last point of the path is a close point to the player position,
//which makes IsValid return true, hence it doesn't work. But we can check if the distance between the lastPoint and the player is 0.0 or not,
//and we get the correct bool like this
bool UC_AIEnemy::ExistsValidPathToPlayer()
{
	UNavigationSystem *navSys = GetWorld()->GetNavigationSystem();
	UNavigationPath *navPath = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), enemy->GetActorLocation(), player->GetActorLocation());
	
	if (!navPath->IsValid()) return false; //This means that navPath has NO points or is not updated or something like that :)

	FVector playerLocation = player->GetActorLocation(); playerLocation.Z = 0.0f;
	FVector lastPathPoint = navPath->PathPoints[navPath->PathPoints.Num() - 1]; lastPathPoint.Z = 0.0f;
	GEngine->AddOnScreenDebugMessage(126, 1.0f, FColor::Green, FString::SanitizeFloat(FVector::Dist(lastPathPoint, playerLocation)));
	return FVector::Dist(lastPathPoint, playerLocation) <= 1.0f;
}

