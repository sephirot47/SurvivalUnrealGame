#include "Survive.h"
#include "C_AIEnemy.h"

UC_AIEnemy::UC_AIEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_AIEnemy::BeginPlay()
{
	Super::BeginPlay();
	enemy = Cast<ASEnemy>(GetOwner());
	player = Cast<ASPlayer>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
}

void UC_AIEnemy::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UNavigationSystem::SimpleMoveToLocation(enemy->GetController(), player->GetActorLocation());
}


