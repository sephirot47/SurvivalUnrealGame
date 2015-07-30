#include "Survive.h"
#include "SWeapon.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	damage = 5.0f;
	weight = 0.1f;
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	player->InputComponent->BindAction("Weapon Use", IE_Pressed, this, &ASWeapon::Use);
}

void ASWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASWeapon::Use()
{
	OnSuccessfulWeaponUse();
}