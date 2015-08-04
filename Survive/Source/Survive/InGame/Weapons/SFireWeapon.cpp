#include "Survive.h"
#include "SFireWeapon.h"

ASFireWeapon::ASFireWeapon()
{
	rateOfFire = 3.0f;

	timeLastShot = 999.9f;
	timeLastReload = 999.9f;

	reloadTime = 2.0f;
	slotAmmo = 10;
	currentAmmo = 999; 
}

void ASFireWeapon::BeginPlay()
{
	Super::BeginPlay();
	player->InputComponent->BindAction("Weapon Reload", IE_Pressed, this, &ASFireWeapon::Reload);
}

void ASFireWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeLastShot += DeltaTime;
	timeLastReload += DeltaTime;
}

void ASFireWeapon::GetTracedActors(TArray<AActor*> &damageReceivers, TArray<FHitResult> &hitResults)
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(this);
	ignoredActors.Add(player);

	FVector start = player->GetShootOrigin();
	FVector end = start + player->GetForward() * 99999.9f;

	TArray<AActor*> actorsHit;
	SUtils::MultiTrace(ignoredActors, start, end, hitResults, damageReceivers);
}


void ASFireWeapon::Use()
{
	ASWeapon::Use();

	if (CanBeUsed()) 
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
	else //Weapon can NOT Be Used 
	{
		OnNotSuccessfulWeaponUse();
	}
}


bool ASFireWeapon::CanBeUsed()
{
	if ( WaitingForRateOfFire() ) return false;
	if ( Reloading() ) return false;
	if( OutOfAmmo() ) return false;
	return true;
}

void ASFireWeapon::Reload()
{
	if ( !Reloading() ) currentAmmo = slotAmmo;
	timeLastReload = 0.0f;
}

float ASFireWeapon::GetRateOfFire() { return rateOfFire; }
float ASFireWeapon::GetReloadTime() { return reloadTime; }
int32 ASFireWeapon::GetSlotAmmo() { return slotAmmo; }
int32 ASFireWeapon::GetCurrentAmmo() { return currentAmmo; }


bool ASFireWeapon::OutOfAmmo() { return currentAmmo <= 0; }
bool ASFireWeapon::Reloading() { return timeLastReload < reloadTime; }
bool ASFireWeapon::WaitingForRateOfFire() { return timeLastShot < 1.0f / rateOfFire; }