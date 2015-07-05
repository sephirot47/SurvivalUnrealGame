#include "Survive.h"
#include "SPlayer.h"


ASPlayer::ASPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

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

