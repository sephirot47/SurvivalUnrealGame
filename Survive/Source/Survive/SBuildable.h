#pragma once

#include "GameFramework/Actor.h"
#include "SBuildable.generated.h"

UENUM(BlueprintType)
enum BuildableState
{
	Building,
	Built
};

UCLASS()
class SURVIVE_API ASBuildable : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere) UMaterial *onBuildingMaterial;
	UPROPERTY(EditAnywhere) UMaterial *onBuiltMaterial;

	BuildableState currentState;

public:	
	ASBuildable();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnBuilding();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnBuilt();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = BuildableState)
		BuildableState GetCurrentState();
};
