#include "Survive.h"
#include "SWeapon.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	damage = 5.0f;
	weight = 0.1f;
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (InputComponent) GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Blue, TEXT("InputComponent Ok"));
	else GEngine->AddOnScreenDebugMessage(2, 10.0f, FColor::Red, TEXT("InputComponent NUUUUUUUUUUUULLL"));
	player->InputComponent->BindAction("Weapon Use", IE_Pressed, this, &ASWeapon::Use);
}

void ASWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

TArray<IDamageReceiver*> ASWeapon::GetTracedActors()
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(this);
	ignoredActors.Add(player);

	FVector start = player->GetShootOrigin();
	FVector end = start + player->GetForward() * 99999.9f;

	TArray<FHitResult> hits;
	TArray<AActor*> actorsHit;
	SUtils::MultiTrace(ignoredActors, start, end, hits, actorsHit);

	TArray<IDamageReceiver*> damageReceivers;
	for (AActor *actorHit : actorsHit)
	{
		IDamageReceiver *damageReceiver = Cast<IDamageReceiver>(actorHit);
		if (damageReceiver) damageReceivers.Add(damageReceiver);
	}

	return damageReceivers;
}

void ASWeapon::Use()
{
	OnSuccessfulWeaponUse();

	TArray<IDamageReceiver*> hits = GetTracedActors();
	for (IDamageReceiver* hit : hits)
	{
		hit->ReceiveDamage(this, damage);
	}
}