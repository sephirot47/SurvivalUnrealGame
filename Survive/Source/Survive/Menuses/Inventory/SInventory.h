#pragma once

#include "GameFramework/Actor.h"
#include "C_SInventoryItem.h"
#include "SInventory.generated.h"


UCLASS()
class SURVIVE_API ASInventory : public AActor
{
	GENERATED_BODY()
private:

	TArray<UC_SInventoryItem*> inventoryItems;

public:	
	ASInventory();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
