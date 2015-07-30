#include "Survive.h"
#include "SWeaponMelee.h"

ASWeaponMelee::ASWeaponMelee()
{
	reloadTime = 2.0f;
	slotAmmo = 10;
	currentAmmo = 0;
}

void ASWeaponMelee::BeginPlay()
{
	Super::BeginPlay();
	player->InputComponent->BindAction("Weapon Reload", IE_Pressed, this, &ASWeaponReloadable::Reload);
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
