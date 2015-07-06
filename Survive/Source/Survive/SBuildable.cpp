#include "Survive.h"
#include "SBuildable.h"


ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;
	onBuildingMaterial = onBuiltMaterial = nullptr;
}

void ASBuildable::BeginPlay()
{
	Super::BeginPlay();
}

void ASBuildable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


void ASBuildable::OnBuilding()
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
	{
		mesh->SetMaterial(0, onBuildingMaterial);
	}

	currentState = Building;
}

void ASBuildable::OnBuilt()
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
	{
		mesh->SetMaterial(0, onBuiltMaterial);
	}

	currentState = Built;
}

void ASBuildable::OnDestroy()
{

}

BuildableState ASBuildable::GetCurrentState()
{
	return currentState;
}

