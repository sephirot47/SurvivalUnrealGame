#pragma once

#include "GameFramework/Actor.h"
#include "../Characters/Player/SPlayer.h"
#include "SWeapon.generated.h"

UCLASS()
class SURVIVE_API ASWeapon : public AActor
{
	GENERATED_BODY()

protected:

	ASPlayer *player;

	UPROPERTY(EditAnywhere, Category = Combat) float damage; //The power of every hit/shot bullet of this weapon
	UPROPERTY(EditAnywhere, Category = Combat) float weight; //The weight of this weapon. Goes from 0 to 1. (0=no slow down), (1=you cant move carrying this weapon)
	
	//Trace in the direction the player(its camera actually) is facing, and return the array of AActors hit/overlapped
	TArray<IDamageReceiver*> GetTracedActors();

public:	

	ASWeapon();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Use(); //Try to use this weapon.
	virtual bool CanBeUsed() { return true; }

	UFUNCTION(BlueprintImplementableEvent, Category = Combat) 
		virtual void OnSuccessfulWeaponUse(); //Called every time this weapon is successfully used

	float GetDamage() { return damage; }
	float GetWeight() { return weight; }
};
