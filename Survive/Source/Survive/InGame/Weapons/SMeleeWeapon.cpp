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
	//OnSuccessfulWeaponUse(nullptr, false, FVector::ZeroVector);
}

bool ASMeleeWeapon::CanBeUsed()
{
	return true;
}
