#pragma once

#include "GameFramework/Actor.h"
#include "../Characters/Player/SPlayer.h"
#include "../Characters/IDamageReceiver.h"
#include "SWeapon.generated.h"

UCLASS()
class SURVIVE_API ASWeapon : public AActor
{
	GENERATED_BODY()

private:
	float timeLastShot;

protected:

	ASPlayer *player;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats") 
		float rateOfFire; //Times this weapon shoots in a second

	bool usingWeapon;

	UPROPERTY(EditAnywhere, Category = Combat) float damage; //The power of every hit/shot bullet of this weapon
	UPROPERTY(EditAnywhere, Category = Combat) float weight; //The weight of this weapon. Goes from 0 to 1. (0=no slow down), (1=you cant move carrying this weapon)

	//This function must be called by child weapons in order to be able to reset the timeLastShot to 0, to keep track of the rate of fire
	void NotifyWeaponUsed() { timeLastShot = 0.0f; }

public:	

	ASWeapon();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	//Try to use this weapon.
	UFUNCTION(BlueprintCallable, Category = Combat) 
		virtual void Use(); 

	virtual bool CanBeUsed();

	UFUNCTION(BlueprintImplementableEvent, Category = Combat) 
		virtual void OnSuccessfulWeaponUse(AActor *damageReceiver, bool hasHit, const FVector& hitPoint); //Called every time this weapon is successfully used

	UFUNCTION(BlueprintImplementableEvent, Category = Combat)
		virtual void OnNotSuccessfulWeaponUse(); //Called every time this weapon is NOT successfully used

	//Rate of Fire
	UFUNCTION(BlueprintCallable, Category = Combat) 
		float GetRateOfFire();

	//Tells if the weapon can be used or not due to rate of fire(being used at a faster rate than permitetd by the weapon)
	UFUNCTION(BlueprintCallable, Category = Combat) 
		bool WaitingForRateOfFire(); 

	void OnWeaponUseInput() { usingWeapon = true; }
	void OnWeaponUnUseInput() { usingWeapon = false;}

	float GetDamage() { return damage; }
	float GetWeight() { return weight; }
};
