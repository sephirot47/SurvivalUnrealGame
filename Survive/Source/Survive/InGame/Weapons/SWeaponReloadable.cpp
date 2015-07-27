#include "Survive.h"
#include "SWeaponReloadable.h"


ASWeaponReloadable::ASWeaponReloadable()
{
	reloadTime = 2.0f;
	slotAmmo = 10;
	currentAmmo = 0;
}

ASWeaponReloadable::~ASWeaponReloadable()
{

}

void ASWeaponReloadable::BeginPlay()
{
	Super::BeginPlay();

}

void ASWeaponReloadable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWeaponReloadable::Use()
{
	ASWeapon::Use();
}


bool ASWeaponReloadable::CanBeUsed()
{
	if (timeLastReload < reloadTime) return currentAmmo > 0;
	return false;
}

void ASWeaponReloadable::Reload()
{
	if (timeLastReload < reloadTime)
		currentAmmo = slotAmmo;
}