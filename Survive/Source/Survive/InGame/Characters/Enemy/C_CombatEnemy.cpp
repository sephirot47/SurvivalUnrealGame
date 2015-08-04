#include "Survive.h"
#include "C_CombatEnemy.h"
#include "../../Buildable/SBuildable.h"


UC_CombatEnemy::UC_CombatEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	attack = 10.0f;
	attackRate = 3.0f;
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

	TArray<IDamageReceiver*> damageReceivers;
	SUtils::GetAll_InARadiusOf<IDamageReceiver>(GetWorld(), enemy, attackRange, damageReceivers, true);
	for (int i = 0; i < damageReceivers.Num(); ++i)
	{
		AActor *actor = Cast<AActor>(damageReceivers[i]);
	}
}

void UC_CombatEnemy::OnTickWithoutAValidPathToPlayer()
{
	if (CanAttack())
	{
		GEngine->AddOnScreenDebugMessage(1234, 1.0f, FColor::Black, TEXT("CAN ATTACK"));
		ASBuildable *buildable = SUtils::GetClosestTo<ASBuildable>(GetWorld(), enemy, attackRange);
		if (buildable) Attack(buildable);
	}
}

bool UC_CombatEnemy::CanAttack()
{
	return timeLastAttack >= (1.0f / attackRate);
}

void UC_CombatEnemy::Attack(IDamageReceiver *damageReceiver)
{
	GEngine->AddOnScreenDebugMessage(12534, 1.0f, FColor::Green, TEXT("ATTACKING"));
	timeLastAttack = 0.0f;
	damageReceiver->ReceiveDamage(enemy, attack);
}