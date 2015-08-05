#include "Survive.h"
#include "InventoryDB.h"

AInventoryDB::AInventoryDB()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInventoryDB::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryDB::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}

/*
int32 AInventoryDB::GetAmmoAmountForThisTypeOfWeapon(TSubclassOf<ASFireWeapon> FireWeaponClass)
{
	int32 ammoAmount = 0;
	for (UInventoryItem *item : items)
	{
	}
	return ammoAmount;
}
*/