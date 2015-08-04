#pragma once

#include "Components/ActorComponent.h"
#include "../../Weapons/SWeapon.h"
#include "SPlayer.h"
#include "../../../SUtils.h"
#include "C_SPlayerWeaponManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerWeaponManager : public UActorComponent
{
	GENERATED_BODY()

private:

	ASWeapon *currentWeapon;
	ASPlayer *player;

	void EquipWeapon(ASWeapon *weapon);
	void UnEquipCurrentWeapon();

public:	

	//This is the socket where the weapon will attach
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Weapon")
		FName weaponSocketName;

	UC_SPlayerWeaponManager();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "Player Weapon")
		void OnWeaponsMenuItemSelected(TSubclassOf<ASWeapon> WeaponClass);

	UFUNCTION(BlueprintCallable, Category = "Player Weapon")
		ASWeapon* GetCurrentWeapon();
};
