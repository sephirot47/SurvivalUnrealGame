#pragma once

#include "Components/ActorComponent.h"
#include "SEnemy.h"
#include "../InGame/Player/SPlayer.h"
#include "../InGame/Buildable/SBuildable.h"
#include "C_CombatEnemy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_CombatEnemy : public UActorComponent
{
	GENERATED_BODY()

private:
	ASEnemy *enemy;
	ASPlayer *player;

public:	
	UC_CombatEnemy();


	//Returns the buildable the enemy has in its attack range in front of him. Returns nullptr if doesn't have one
	ASBuildable* GetBuildableInFront();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
