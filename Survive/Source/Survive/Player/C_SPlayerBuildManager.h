// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SBuildable.h"
#include "C_SPlayerBuildManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerBuildManager : public UActorComponent
{
	GENERATED_BODY()

	ACharacter *character;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *targetBuildable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *lastTargetBuildable;

	UC_SPlayerBuildManager();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OnInputRemoveBuildable();
};
