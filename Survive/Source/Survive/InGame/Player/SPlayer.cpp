#include "Survive.h"
#include "SPlayer.h"


ASPlayer::ASPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	maxHealth = 100.0f;
	health = maxHealth * 0.6f;
}

void ASPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ASPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float ASPlayer::GetHealthPercent() 
{ 
	return health / maxHealth;
}
