#include "Survive.h"
#include "SEnemy.h"

ASEnemy::ASEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

