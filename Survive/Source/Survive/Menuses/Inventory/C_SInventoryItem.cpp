#include "Survive.h"
#include "C_SInventoryItem.h"


UC_SInventoryItem::UC_SInventoryItem()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_SInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void UC_SInventoryItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

