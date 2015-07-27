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
	
}

void ASWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASWeapon::Use()
{
	OnSuccessfulWeaponUse();
}