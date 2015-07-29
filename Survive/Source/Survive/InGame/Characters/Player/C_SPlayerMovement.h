#pragma once

#include "SPlayer.h"

#include "Components/ActorComponent.h"
#include "C_SPlayerMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerMovement : public UActorComponent
{
	GENERATED_BODY()

private:
	ASPlayer *player;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		FVector2D pitchLimits;

public:

	UC_SPlayerMovement();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation")
		USkeletalMeshComponent *arms;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleMoveX(float v);
	void HandleMoveY(float v);
	void HandleTurnX(float v);
	void HandleTurnY(float v);
};
