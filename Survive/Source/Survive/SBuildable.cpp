#include "Survive.h"
#include "SBuildable.h"


ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;

	onBuildingMaterial = nullptr;
	onBuiltMaterial = nullptr;
	onPointingOverMaterial = nullptr;
	onSelectedMaterial = nullptr;

	currentState = Built;
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
	ChangeMaterial(onBuildingMaterial);
	currentState = Building;
}

void ASBuildable::OnBuilt()
{
	ChangeMaterial(onBuiltMaterial);
	currentState = Built;
}

void ASBuildable::OnPointingOver()
{
	ChangeMaterial(onPointingOverMaterial);
	currentState = PointingOver;
}

//Trigers between selected / unselected(built)
void ASBuildable::OnSelect()
{
	if (currentState == Selected) OnBuilt();
	else
	{
		ChangeMaterial(onSelectedMaterial);
		currentState = Selected;
	}
}


void ASBuildable::OnDestroy()
{

}

BuildableState ASBuildable::GetCurrentState()
{
	return currentState;
}

void ASBuildable::ChangeMaterial(UMaterial *material)
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
		mesh->SetMaterial(0, material);
}