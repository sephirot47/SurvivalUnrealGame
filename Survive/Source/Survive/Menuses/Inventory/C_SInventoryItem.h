#pragma once

#include "Components/ActorComponent.h"
#include "C_SInventoryItem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SInventoryItem : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Info")
		UTexture *image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Info")
		FString name;

	UC_SInventoryItem();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
