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


TSubclassOf<ASBuildable> ABuildingsDB::GetBuildingClassFromId(int32 id)
{
	for (int i = 0; i < buildingItems.Num(); ++i)
	{
		if (buildingItems[i].id == id)
		{
			return buildingItems[i].buildableClass;
		}
	}

	return nullptr;
}