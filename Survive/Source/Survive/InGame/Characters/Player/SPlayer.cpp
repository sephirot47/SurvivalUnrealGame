#include "Survive.h"
#include "SPlayer.h"


ASPlayer::ASPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	maxHealth = 100.0f;
	health = maxHealth;
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

FVector ASPlayer::GetShootOrigin()
{
	return GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
}

FVector ASPlayer::GetForward()
{
	return GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();
}

UC_SPlayerBuildManager* ASPlayer::GetBuildManager()
{
	TArray<UC_SPlayerBuildManager*> components;
	GetComponents(components);
	return components[0];
}

USkeletalMeshComponent* ASPlayer::GetArms()
{
	TArray<USkeletalMeshComponent*> comp;
	GetComponents(comp);
	return comp[0];
}

float ASPlayer::GetHealthPercent() 
{ 
	return health / maxHealth;
}

void ASPlayer::ReceiveDamage(AActor* originActor, float damage)
{
	health -= damage;
	if (health <= 0) this->Destroy();
}