#include "Survive.h"
#include "C_CombatEnemy.h"
#include "../../Buildable/SBuildable.h"


UC_CombatEnemy::UC_CombatEnemy()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	attack = 10.0f;
	attackRate = 3.0f;
	attackRange = 10.0f;

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

	TArray<ASPlayer*> playersFound;
	SUtils::GetVisibleFrom<ASPlayer>(GetWorld(), enemy, playersFound, 700.0f, true);
	if (playersFound.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::White, TEXT("PLAYER VISIBLE"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::White, TEXT("PLAYER NOOOOOOT VISIBLE"));
	}

	//When the enemy can't reach the player, this means he has a buildable in front of him
	if (enemy->GetVelocity().IsZero())
	{
		if (timeLastAttack >= 1.0f / attackRate)
		{
			ASBuildable *buildable = SUtils::GetClosestTo<ASBuildable>(GetWorld(), enemy);
			if (buildable) Attack(buildable);
		}
	}

	TArray<IDamageReceiver*> damageReceivers;
	SUtils::GetAll_InARadiusOf<IDamageReceiver>(GetWorld(), enemy, 700.0f, damageReceivers, true);
	for (int i = 0; i < damageReceivers.Num(); ++i)
	{
		AActor *actor = Cast<AActor>(damageReceivers[i]);
	}
}

void UC_CombatEnemy::Attack(IDamageReceiver *damageReceiver)
{
	timeLastAttack = 0.0f;
	damageReceiver->ReceiveDamage(enemy, attack);
	GEngine->AddOnScreenDebugMessage(125, 1.0f, FColor::Red, TEXT("ATTACK!"));
}