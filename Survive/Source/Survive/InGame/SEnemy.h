#pragma once

#include "GameFramework/Character.h"
#include "SEnemy.generated.h"

UCLASS()
class SURVIVE_API ASEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	float maxLife, life;
	float speed;
	
public:
	ASEnemy();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	float GetMaxLife() { return maxLife; }
	float GetLife() { return life; }
	float GetSpeed() { return speed; }
};
