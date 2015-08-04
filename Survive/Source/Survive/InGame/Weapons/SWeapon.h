#pragma once

#include "GameFramework/Actor.h"
#include "../Characters/Player/SPlayer.h"
#include "../Characters/IDamageReceiver.h"
#include "SWeapon.generated.h"

UCLASS()
class SURVIVE_API ASWeapon : public AActor
{
	GENERATED_BODY()

protected:

	ASPlayer *player;
	
	bool usingWeapon;

	UPROPERTY(EditAnywhere, Category = Combat) float damage; //The power of every hit/shot bullet of this weapon
	UPROPERTY(EditAnywhere, Category = Combat) float weight; //The weight of this weapon. Goes from 0 to 1. (0=no slow down), (1=you cant move carrying this weapon)

public:	

	ASWeapon();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Combat) virtual void Use(); //Try to use this weapon.

	virtual bool CanBeUsed() { return true; }

	UFUNCTION(BlueprintImplementableEvent, Category = Combat) 
		virtual void OnSuccessfulWeaponUse(AActor *damageReceiver, bool hasHit, const FVector& hitPoint); //Called every time this weapon is successfully used

	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
		virtual void OnNotSuccessfulWeaponUse(); //Called every time this weapon is NOT successfully used

	void OnWeaponUseInput() { usingWeapon = true; }
	void OnWeaponUnUseInput() { usingWeapon = false;}

	float GetDamage() { return damage; }
	float GetWeight() { return weight; }
};
