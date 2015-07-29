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
}

void ASWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	TArray<IDamageReceiver*> hits = GetTracedActors();
	GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::White, FString::FromInt(hits.Num()));
	int i = 100;
	for (IDamageReceiver* hit : hits)
	{
		GEngine->AddOnScreenDebugMessage(++i, 0.1f, FColor::White, Cast<AActor>(hit)->GetName());
	}
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
	int i = 999;
	for (AActor *actorHit : actorsHit)
	{
		GEngine->AddOnScreenDebugMessage(++i, 0.1f, FColor::Red, actorHit->GetName());
		IDamageReceiver *damageReceiver = Cast<IDamageReceiver>(actorHit);
		if (damageReceiver) damageReceivers.Add(damageReceiver);
	}

	return damageReceivers;
}

void ASWeapon::Use()
{
	OnSuccessfulWeaponUse();

}