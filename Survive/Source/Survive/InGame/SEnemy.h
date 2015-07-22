#pragma once

#include "GameFramework/Character.h"
#include "SEnemy.generated.h"

UCLASS()
class SURVIVE_API ASEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ASEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float maxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float life;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float speed;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	float GetMaxLife() { return maxLife; }
	float GetLife() { return life; }
	float GetSpeed() { return speed; }
};
