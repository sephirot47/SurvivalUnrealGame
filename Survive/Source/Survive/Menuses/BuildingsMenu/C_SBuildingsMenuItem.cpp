#include "Survive.h"
#include "C_SBuildingsMenuItem.h"


UC_SBuildingsMenuItem::UC_SBuildingsMenuItem()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_SBuildingsMenuItem::BeginPlay()
{
	Super::BeginPlay();	
}


void UC_SBuildingsMenuItem::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

