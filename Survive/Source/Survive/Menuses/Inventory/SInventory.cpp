#include "Survive.h"
#include "SInventory.h"


ASInventory::ASInventory()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASInventory::BeginPlay()
{
	Super::BeginPlay();
}

void ASInventory::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

