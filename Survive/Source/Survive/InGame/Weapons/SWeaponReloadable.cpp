#include "Survive.h"
#include "SWeaponReloadable.h"


ASWeaponReloadable::ASWeaponReloadable()
{
	rateOfFire = 1.0f;

	timeLastShot = 999.9f;
	timeLastReload = 999.9f;

	reloadTime = 2.0f;
	slotAmmo = 10;
	currentAmmo = 999; 
}

void ASWeaponReloadable::BeginPlay()
{
	Super::BeginPlay();
	player->InputComponent->BindAction("Weapon Reload", IE_Pressed, this, &ASWeaponReloadable::Reload);
}

void ASWeaponReloadable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeLastShot += DeltaTime;
	timeLastReload += DeltaTime;
}

void ASWeaponReloadable::GetTracedActors(TArray<AActor*> &damageReceivers, TArray<FHitResult> &hitResults)
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(this);
	ignoredActors.Add(player);

	FVector start = player->GetShootOrigin();
	FVector end = start + player->GetForward() * 99999.9f;

	TArray<AActor*> actorsHit;
	SUtils::MultiTrace(ignoredActors, start, end, hitResults, damageReceivers);
}


void ASWeaponReloadable::Use()
{
	ASWeapon::Use();

	if (!CanBeUsed()) OnNotSuccessfulWeaponUse();
	else
	{
		timeLastShot = 0.0f;
		--currentAmmo;

		TArray<AActor*> damageReceivers;
		TArray<FHitResult> hits;
		GetTracedActors(damageReceivers, hits);

		if (damageReceivers.Num() > 0)
		{
			//Successful, and hit an Actor
			AActor* actorHit = damageReceivers[0];
			FHitResult *hit = &hits[0];
			OnSuccessfulWeaponUse(actorHit, true, hit->Location);

			//If the actor is a damage receiver, damage it
			IDamageReceiver* dmgReceiver = Cast<IDamageReceiver>(actorHit);
			if (dmgReceiver) dmgReceiver->ReceiveDamage(this, damage);
		}
		else OnSuccessfulWeaponUse(nullptr, false, FVector::ZeroVector); //Successful, but didnt hit any Actor
	}
}


bool ASWeaponReloadable::CanBeUsed()
{
	if (timeLastShot < 1.0f / rateOfFire) return false;
	if (timeLastReload < reloadTime) return false;
	if(currentAmmo <= 0) return false;
	return true;
}

void ASWeaponReloadable::Reload()
{
	if (timeLastReload >= reloadTime) currentAmmo = slotAmmo;
	timeLastReload = 0.0f;
}