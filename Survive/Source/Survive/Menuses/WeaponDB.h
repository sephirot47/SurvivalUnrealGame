#pragma once

#include "GameFramework/Actor.h"
#include "../InGame/Weapons/SWeapon.h"
#include "WeaponDB.generated.h"

USTRUCT(BlueprintType)
struct FWeaponItemDB
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D *thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<ASWeapon> weaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 totalAmmoOutOfSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 ammoInSlot;
};

UCLASS()
class SURVIVE_API AWeaponDB : public AActor
{
	GENERATED_BODY()
	
public:	


	//The array of weapon items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Items")
		TArray<FWeaponItemDB> weaponItems;

	AWeaponDB();

	UFUNCTION(BlueprintCallable, Category = "Weapon Items")
		TSubclassOf<ASWeapon> GetWeaponClassFromId(int32 id);

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
