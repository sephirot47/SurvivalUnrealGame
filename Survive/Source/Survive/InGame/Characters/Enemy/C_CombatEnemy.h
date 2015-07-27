#pragma once

#include "Components/ActorComponent.h"
#include "SEnemy.h"
#include "../IDamageReceiver.h"
#include "../Player/SPlayer.h"
#include "../../Buildable/SBuildable.h"
#include "C_CombatEnemy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_CombatEnemy : public UActorComponent, public IDamageReceiver
{
	GENERATED_BODY()

private:
	ASEnemy *enemy;
	ASPlayer *player;


	UPROPERTY(EditAnywhere, Category = "Stats") float maxLife;
	UPROPERTY(EditAnywhere, Category = "Stats") float life;
	UPROPERTY(EditAnywhere, Category = "Stats") float attack; //Attack force
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRate; //Times the enemy attacks per second
	UPROPERTY(EditAnywhere, Category = "Stats") float attackRange; //Maximum distance from enemy to player to attack

	float timeLastAttack;

public:	
	UC_CombatEnemy();


	//Returns the buildable the enemy has in its attack range in front of him. Returns nullptr if doesn't have one
	ASBuildable* GetBuildableInFront();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void Attack(IDamageReceiver *damageReceiver);
	virtual void ReceiveDamage(AActor* originActor, float damage) override;
};
