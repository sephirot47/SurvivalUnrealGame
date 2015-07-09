#pragma once

#include "Components/ActorComponent.h"
#include "C_SBuildingsMenuItem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SBuildingsMenuItem : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings Item Info")
		UTexture *image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings Item Info")
		FString name;

	UC_SBuildingsMenuItem();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
