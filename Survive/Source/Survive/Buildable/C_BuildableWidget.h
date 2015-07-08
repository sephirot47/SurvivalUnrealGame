#pragma once

#include "Components/ActorComponent.h"
#include "C_BuildableWidget.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_BuildableWidget : public UActorComponent
{
	GENERATED_BODY()

private:

public:
	UC_BuildableWidget();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
