#include "Survive.h"
#include "C_BuildableWidget.h"

UC_BuildableWidget::UC_BuildableWidget()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_BuildableWidget::BeginPlay()
{
	Super::BeginPlay();
}


void UC_BuildableWidget::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

