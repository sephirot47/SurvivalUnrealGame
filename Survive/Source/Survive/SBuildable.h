#pragma once

#include "GameFramework/Actor.h"
#include "SBuildable.generated.h"

UENUM(BlueprintType)
enum BuildableState
{
	Building,		  //When the player is positioning this building
	Built,			  //Default state
	PointingOver,     //When the player is pointing this building
};

UCLASS()
class SURVIVE_API ASBuildable : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere) UMaterial *onBuildingMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onBuiltMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onPointingOverMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onSelectedMaterial;

	BuildableState currentState;

	void ChangeMaterial(UMaterial *material);

public:	
	ASBuildable();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnBuilding();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnBuilt();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnPointingOver();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		BuildableState GetCurrentState();
};
