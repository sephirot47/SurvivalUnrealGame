#include "Survive.h"
#include "C_CombatEnemy.h"


UC_CombatEnemy::UC_CombatEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_CombatEnemy::BeginPlay()
{
	Super::BeginPlay();
	enemy = Cast<ASEnemy>(GetOwner());
	player = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}


void UC_CombatEnemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//When the enemy can't reach the player, this means he has a buildable in front of him
	if (enemy->GetVelocity().IsZero())
	{
		GEngine->AddOnScreenDebugMessage(123, 1.0f, FColor::Blue, TEXT("Can't reach player"));
		ASBuildable *buildable = GetBuildableInFront();
		if (buildable)
		{
			GEngine->AddOnScreenDebugMessage(124, 1.0f, FColor::Red, TEXT("DESTROY BUILDABLE!"));
			buildable->OnDestroy();
		}
		else
			GEngine->AddOnScreenDebugMessage(125, 1.0f, FColor::Red, TEXT("No buildable :("));
	}
}

ASBuildable* UC_CombatEnemy::GetBuildableInFront()
{
	FVector start = enemy->GetActorLocation();
	FVector end = enemy->GetActorForwardVector() * enemy->attackRange;
	TArray<AActor*> ignore;
	FHitResult hitResult;
	AActor *actor = SUtils::Trace(ignore, start, end, PlayerPointingTraceChannel);
	if (actor) GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, actor->GetName());
	else GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, TEXT("No actor*!"));
	if (actor != nullptr) return Cast<ASBuildable>(actor);
	return nullptr;
}