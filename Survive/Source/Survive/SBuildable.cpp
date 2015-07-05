#include "Survive.h"
#include "SBuildable.h"


ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;
	
	onBuildMaterial = nullptr;
}

void ASBuildable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBuildable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

