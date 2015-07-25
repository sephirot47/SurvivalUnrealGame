#pragma once

#include "GameFramework/Character.h"
#include "SEnemy.generated.h"

UCLASS()
class SURVIVE_API ASEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ASEnemy();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
