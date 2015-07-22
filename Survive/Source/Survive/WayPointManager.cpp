#include "Survive.h"
#include "WayPointManager.h"

TArray<FVector> WayPointManager::waypoints = TArray<FVector>();

void WayPointManager::GetAllWaypoints(UWorld *world)
{
	waypoints.Empty();

	for (TActorIterator<AActor> actor(world); actor; ++actor)
	{
		ASBuildable *buildable = Cast<ASBuildable>(*actor);
		if (buildable) buildable->AddWaypointsToArray(waypoints);
	}
}

void WayPointManager::RecalculateWaypointGraph(UWorld *world)
{
	GetAllWaypoints(world); 
	
	int i = 0;  for (auto wp : waypoints) GEngine->AddOnScreenDebugMessage(++i, 1.0f, FColor::Green, wp.ToString());
}
