#include "Survive.h"
#include "C_CombatEnemy.h"


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

	//When the enemy can't reach the player, this means he has a buildable in front of him
	if (enemy->GetVelocity().IsZero())
	{
		if (timeLastAttack >= 1.0f / attackRate)
		{
			ASBuildable *buildable = GetBuildableInFront();
			if (buildable) Attack(buildable);
		}
	}
}

ASBuildable* UC_CombatEnemy::GetBuildableInFront()
{
	FVector start = enemy->GetActorLocation();
	FVector end = enemy->GetActorForwardVector() * attackRange;
	TArray<AActor*> ignore;
	FHitResult hitResult;
	AActor *actor = SUtils::Trace(ignore, start, end, PlayerPointingTraceChannel);
	if (actor) GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, actor->GetName());
	if (actor != nullptr) return Cast<ASBuildable>(actor);
	return nullptr;
}

void UC_CombatEnemy::Attack(IDamageReceiver *damageReceiver)
{
	timeLastAttack = 0.0f;
	damageReceiver->ReceiveDamage(enemy, attack);
	GEngine->AddOnScreenDebugMessage(125, 1.0f, FColor::Red, TEXT("ATTACK!"));
}