#pragma once

#include "Object.h"
#include "InventoryItem.generated.h"

UCLASS()
class SURVIVE_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D *thumbnail;
};
