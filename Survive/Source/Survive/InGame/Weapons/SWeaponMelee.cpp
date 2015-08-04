#include "Survive.h"
#include "SWeaponMelee.h"

ASWeaponMelee::ASWeaponMelee()
{
}

void ASWeaponMelee::BeginPlay()
{
	Super::BeginPlay();
}

void ASWeaponMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWeaponMelee::Use()
{
	ASWeapon::Use();
	//OnSuccessfulWeaponUse(nullptr, false, FVector::ZeroVector);
}

bool ASWeaponMelee::CanBeUsed()
{
	return true;
}
