#include "Survive.h"
#include "BuildingsDB.h"

ABuildingsDB::ABuildingsDB()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABuildingsDB::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingsDB::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}