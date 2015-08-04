#include "Survive.h"
#include "SEnemy.h"

ASEnemy::ASEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	maxHealth = 100.0f;
	health = maxHealth;
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

void ASEnemy::ReceiveDamage(AActor* originActor, float damage)
{
	health -= damage;
	if (health <= 0) this->Destroy();
}