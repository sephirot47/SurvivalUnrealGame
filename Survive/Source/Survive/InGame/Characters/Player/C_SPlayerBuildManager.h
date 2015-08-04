// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "../../Buildable/SBuildable.h"
#include "C_SPlayerBuildManager.generated.h"


UENUM(BlueprintType)
enum PlayerBuildingState
{
	PointingBuildable,
	MovingBuildable
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerBuildManager : public UActorComponent
{
	GENERATED_BODY()

	ACharacter *character;
	PlayerBuildingState currentState;

	bool rotateInputDown;

	bool BuildableInRange(ASBuildable *buildable);
	bool BuildableInRange(const FVector &buildableLocation);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *targetBuildable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *lastTargetBuildable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Point")
		FVector targetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		float buildableSelectionRange;


	UC_SPlayerBuildManager();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OnInputMoveBuildable();
	void OnInputPutBuildable();
	void OnInputRotateBuildableDown();
	void RotateTargetBuildable();
	void OnInputRotateBuildableUp();
	void OnInputRemoveBuildable();


	UFUNCTION(BlueprintCallable, Category = "Player Building")
		void OnBuildingsMenuItemSelected(TSubclassOf<ASBuildable> BuildableClass);

	//Fills the targetBuildable and targetPoint variables, tracing the rays and stuff
	UFUNCTION(BlueprintCallable, Category = "Player Building Target")
		void FillTargetBuildableInfo();

	UFUNCTION(BlueprintCallable, Category = "Player Building State")
		PlayerBuildingState GetCurrentBuildingState();
};
