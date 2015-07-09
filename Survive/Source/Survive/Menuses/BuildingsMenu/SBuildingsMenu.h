#pragma once

#include "GameFramework/Actor.h"
#include "C_SBuildingsMenuItem.h"
#include "SBuildingsMenu.generated.h"

UCLASS()
class SURVIVE_API ASBuildingsMenu : public AActor
{
	GENERATED_BODY()

private:
	TArray<UC_SBuildingsMenuItem*> buildingsItems;
	
public:	
	ASBuildingsMenu();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
};
