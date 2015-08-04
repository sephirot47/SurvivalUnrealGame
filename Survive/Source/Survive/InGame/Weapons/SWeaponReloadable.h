#pragma once

#include "InGame/Weapons/SWeapon.h"
#include "SWeaponReloadable.generated.h"

UCLASS()
class SURVIVE_API ASWeaponReloadable : public ASWeapon
{
	GENERATED_BODY()

private:

	float timeLastShot;
	float timeLastReload; //Keeps track of the time passed since the weapon started to reload

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon Stats") float rateOfFire; //Times this weapon shoots in a second

	UPROPERTY(EditAnywhere, Category = Ammo) float reloadTime; //The reload time it takes to reload this weapon
	UPROPERTY(EditAnywhere, Category = Ammo) int32 slotAmmo; //The maximum ammo for slot
	UPROPERTY(EditAnywhere, Category = Ammo) int32 currentAmmo; //The current ammo in the slot

	//Trace in the direction the player(its camera actually) is facing, and return the array of AActors hit/overlapped
	void GetTracedActors(TArray<AActor*> &damageReceivers, TArray<FHitResult> &hitResults);

public:

	ASWeaponReloadable();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Use() override;
	virtual bool CanBeUsed() override;

	virtual void Reload();

	UFUNCTION(BlueprintImplementableEvent, Category = Reload) 
		void OnReload();
};
