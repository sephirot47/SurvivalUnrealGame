#pragma once

#include "Components/ActorComponent.h"
#include "SEnemy.h"
#include "../InGame/Player/SPlayer.h"
#include "C_AIEnemy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_AIEnemy : public UActorComponent
{
	GENERATED_BODY()

private:
	ASEnemy *enemy;
	ASPlayer *player;

	void FollowPlayerDirectly(float DeltaTime);

public:	
	UC_AIEnemy();

	virtual void BeginPlay() override;	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
