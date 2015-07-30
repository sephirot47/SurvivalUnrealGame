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

