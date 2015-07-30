#include "Survive.h"
#include "SWeaponReloadable.h"


ASWeaponReloadable::ASWeaponReloadable()
{
	reloadTime = 2.0f;
	slotAmmo = 10;
	currentAmmo = 0;
}

void ASWeaponReloadable::BeginPlay()
{
	Super::BeginPlay();
	player->InputComponent->BindAction("Weapon Reload", IE_Pressed, this, &ASWeaponReloadable::Reload);
}

void ASWeaponReloadable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<IDamageReceiver*> ASWeaponReloadable::GetTracedActors()
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


void ASWeaponReloadable::Use()
{
	ASWeapon::Use();

	TArray<IDamageReceiver*> hits = GetTracedActors();
	for (IDamageReceiver* hit : hits)
	{
		hit->ReceiveDamage(this, damage);
	}
}


bool ASWeaponReloadable::CanBeUsed()
{
	if (timeLastReload < reloadTime) return currentAmmo > 0;
	return false;
}

void ASWeaponReloadable::Reload()
{
	if (timeLastReload < reloadTime)
		currentAmmo = slotAmmo;
}