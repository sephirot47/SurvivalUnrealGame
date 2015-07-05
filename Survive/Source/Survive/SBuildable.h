#pragma once

#include "GameFramework/Actor.h"
#include "SBuildable.generated.h"

UCLASS()
class SURVIVE_API ASBuildable : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere) UMaterial *onBuildMaterial;

public:	
	ASBuildable();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
