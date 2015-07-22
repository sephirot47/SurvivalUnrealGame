#pragma once

#include "GameFramework/Actor.h"
#include "InGame/Buildable/SBuildable.h"
#include "Survive.h"

class SURVIVE_API WayPointManager
{
private:
	static TArray<FVector> waypoints;

	//Fills the waypoints Array with all the waypoints in the world (from buildables)
	static void GetAllWaypoints(UWorld *world);

public:

	static void RecalculateWaypointGraph(UWorld *world);
};
