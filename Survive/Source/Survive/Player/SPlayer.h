#pragma once

#include "GameFramework/Character.h"
#include "SPlayer.generated.h"

UCLASS()
class SURVIVE_API ASPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ASPlayer();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
