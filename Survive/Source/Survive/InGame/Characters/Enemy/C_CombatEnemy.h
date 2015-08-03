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

	UPROPERTY(EditAnywhere, Category = "Stats") float attack; //Attack force
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRate; //Times the enemy attacks per second
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRange; //Maximum distance from enemy to player to attack

	float timeLastAttack;

public:	
	UC_CombatEnemy();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void Attack(IDamageReceiver *damageReceiver);
};
