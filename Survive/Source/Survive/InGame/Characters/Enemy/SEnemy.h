#pragma once

#include "GameFramework/Character.h"
#include "../IDamageReceiver.h"
#include "SEnemy.generated.h"

UCLASS()
class SURVIVE_API ASEnemy : public ACharacter, public IDamageReceiver
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Stats") float maxHealth;
	UPROPERTY(EditAnywhere, Category = "Stats") float health;

public:
	ASEnemy();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void ReceiveDamage(AActor* originActor, float damage) override;
};
