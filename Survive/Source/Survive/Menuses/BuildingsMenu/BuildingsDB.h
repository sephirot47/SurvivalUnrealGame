#pragma once

#include "GameFramework/Actor.h"
#include "../../InGame/Buildable/SBuildable.h"
#include "BuildingsDB.generated.h"

USTRUCT(BlueprintType)
struct FBuildingItemDB
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture2D *thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<ASBuildable> buildableClass;
};

UCLASS()
class SURVIVE_API ABuildingsDB : public AActor
{
	GENERATED_BODY()
	
public:	

	//The array of building items the player can choose to build
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Items")
		TArray<FBuildingItemDB> buildingItems;

	ABuildingsDB();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
