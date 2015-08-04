#pragma once

#include "InGame/Weapons/SWeapon.h"
#include "SMeleeWeapon.generated.h"

UCLASS()
class SURVIVE_API ASMeleeWeapon : public ASWeapon
{
	GENERATED_BODY()
	

public:

	ASMeleeWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Use() override;
	virtual bool CanBeUsed() override;
};
