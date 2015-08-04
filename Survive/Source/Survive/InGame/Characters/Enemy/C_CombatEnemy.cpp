#include "Survive.h"
#include "C_CombatEnemy.h"
#include "../../Buildable/SBuildable.h"


UC_CombatEnemy::UC_CombatEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	attack = 5.0f;
	attackRate = 1.0f;
	attackRange = 300.0f;

	timeLastAttack = 0.0f;
}

void UC_CombatEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	enemy = Cast<ASEnemy>(GetOwner());
	player = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}


void UC_CombatEnemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	timeLastAttack += DeltaTime;

	TArray<ASPlayer*> players;
	SUtils::GetAll_InARadiusOf<ASPlayer>(GetWorld(), enemy, attackRange, players, true);
	for (int i = 0; i < players.Num(); ++i)
	{
		ASPlayer *player = players[i];
		Attack(player);
	}
}

void UC_CombatEnemy::OnTickWithoutAValidPathToPlayer()
{
	if (CanAttack())
	{
		ASBuildable *buildable = SUtils::GetClosestTo<ASBuildable>(GetWorld(), enemy, attackRange);
		if (buildable && !buildable->GetCurrentState() == BuildableState::Building) 
			Attack(buildable);
	}
}

bool UC_CombatEnemy::CanAttack()
{
	return timeLastAttack >= (1.0f / attackRate);
}

void UC_CombatEnemy::Attack(IDamageReceiver *damageReceiver)
{
	if (!CanAttack()) return;

	GEngine->AddOnScreenDebugMessage(12534, 1.0f, FColor::Green, TEXT("ATTACKING"));
	timeLastAttack = 0.0f;
	damageReceiver->ReceiveDamage(enemy, attack);
}