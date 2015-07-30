#pragma once

#include "InGame/Weapons/SWeapon.h"
#include "SWeaponMelee.generated.h"

UCLASS()
class SURVIVE_API ASWeaponMelee : public ASWeapon
{
	GENERATED_BODY()
	

public:

	ASWeaponMelee();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Use() override;
	virtual bool CanBeUsed() override;
};
