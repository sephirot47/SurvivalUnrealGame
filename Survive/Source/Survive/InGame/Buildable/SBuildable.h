#pragma once

#include "GameFramework/Actor.h"
#include "../IDamageReceiver.h"
#include "SBuildable.generated.h"

UENUM(BlueprintType)
enum BuildableState
{
	Building,		  //When the player is positioning this building
	Built,			  //Default state
	PointingOver     //When the player is pointing this building
};

UENUM(BlueprintType)
enum BuildableMaterial
{
	BuildingMaterial,
	WrongBuildingMaterial,
	BuiltMaterial,
	PointingOverMaterial,
	SelectedMaterial
};

UCLASS()
class SURVIVE_API ASBuildable : public AActor, public IDamageReceiver
{
	GENERATED_BODY()
	
private:

	BuildableMaterial currentMaterial;
	BuildableState currentState;

	UPROPERTY(EditAnywhere, Category = "Material") FColor colorBuildingMaterial;
	UPROPERTY(EditAnywhere, Category = "Material") FColor colorWrongBuildingMaterial;
	UPROPERTY(EditAnywhere, Category = "Material") FColor colorBuiltMaterial;
	UPROPERTY(EditAnywhere, Category = "Material") FColor colorPointingOverMaterial;
	UPROPERTY(EditAnywhere, Category = "Material") FColor colorSelectedMaterial;

	float rotationSpeed;
	bool isOverlapping;

	FLinearColor GetCurrentMaterialColor();
	void ChangeMaterial(BuildableMaterial material);
	void ApplyCurrentMaterialColors();

public:	

	//dynamicMaterial is set in the construction script of SBuildable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material") UMaterialInstanceDynamic *dynamicMaterialOpaque;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material") UMaterialInstanceDynamic *dynamicMaterialTranslucent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float maxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float life;

	ASBuildable();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnBuilding();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnBuilt();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnPointingOver();

	UFUNCTION(BlueprintNativeEvent, Category = BuildableState)
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		BuildableState GetCurrentState();

	void SetCollidableWithPlayer(bool collidableWithPlayer);

	inline bool CanBeBuilt() { return !isOverlapping; }
	inline float GetRotationSpeed() { return rotationSpeed; }

	virtual void ReceiveDamage(AActor* originActor, float damage) override;

	UFUNCTION(BlueprintNativeEvent, Category = Damage)
		void OnReceiveDamage(AActor* originActor, float damage);
};
