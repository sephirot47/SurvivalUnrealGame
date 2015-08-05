#include "Survive.h"
#include "SMeleeWeapon.h"

ASMeleeWeapon::ASMeleeWeapon()
{
}

void ASMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMeleeWeapon::Use()
{
	ASWeapon::Use();
	if (CanBeUsed())
	{
		OnSuccessfulWeaponUse(nullptr, false, FVector::ZeroVector);
	}
	else OnNotSuccessfulWeaponUse();
}

bool ASMeleeWeapon::CanBeUsed()
{
	return true;
}
