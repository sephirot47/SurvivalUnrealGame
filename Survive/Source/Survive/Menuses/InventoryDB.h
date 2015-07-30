#pragma once

#include "GameFramework/Actor.h"
#include "InventoryItem.h"
#include "InventoryDB.generated.h"

UCLASS()
class SURVIVE_API AInventoryDB : public AActor
{
	GENERATED_BODY()
	
public:	

	//The array of weapon items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Items")
		TArray<UInventoryItem*> items;

	AInventoryDB();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
