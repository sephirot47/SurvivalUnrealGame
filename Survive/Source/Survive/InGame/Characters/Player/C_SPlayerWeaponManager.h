#pragma once

#include "Components/ActorComponent.h"
#include "../../Weapons/SWeapon.h"
#include "C_SPlayerWeaponManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerWeaponManager : public UActorComponent
{
	GENERATED_BODY()

private:
	ASWeapon *currentWeapon;

	void EquipWeapon(ASWeapon *weapon);
	void UnEquipCurrentWeapon();

public:	
	UC_SPlayerWeaponManager();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "Player Weapon")
		void OnWeaponsMenuItemSelected(TSubclassOf<ASWeapon> WeaponClass);
};
