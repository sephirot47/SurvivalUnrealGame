#pragma once

#include "GameFramework/Character.h"
#include "C_SPlayerBuildManager.h"
#include "SPlayer.generated.h"

UCLASS()
class SURVIVE_API ASPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats) float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats) float maxHealth;

public:
	ASPlayer();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UC_SPlayerBuildManager*  GetBuildManager();

	UFUNCTION(BlueprintCallable, Category = SK_Mesh) USkeletalMeshComponent* GetArms();

	UFUNCTION(BlueprintCallable, Category = Stats) 
	float GetHealthPercent();
};
