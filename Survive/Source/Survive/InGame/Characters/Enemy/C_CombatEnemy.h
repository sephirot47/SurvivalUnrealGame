#pragma once

#include "Components/ActorComponent.h"
#include "SEnemy.h"
#include "../Player/SPlayer.h"
#include "../../Buildable/SBuildable.h"
#include "C_CombatEnemy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_CombatEnemy : public UActorComponent
{
	GENERATED_BODY()

private:
	ASEnemy *enemy;
	ASPlayer *player;

	//Attack force
	UPROPERTY(EditAnywhere, Category = "Stats") float attack; 

	//Times the enemy attacks per second
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRate; 

	//Maximum distance from enemy to player to attack
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRange; 

	//Elapsed time since last attack was successfully done.
	float timeLastAttack;

	virtual bool CanAttack();

public:	
	UC_CombatEnemy();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void OnTickWithoutAValidPathToPlayer();
	virtual void Attack(IDamageReceiver *damageReceiver);
};
