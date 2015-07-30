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

}


bool ASWeaponMelee::CanBeUsed()
{
	return true;
}
