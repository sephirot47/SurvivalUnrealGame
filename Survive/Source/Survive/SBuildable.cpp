#include "Survive.h"
#include "SBuildable.h"

ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;

	onBuildingMaterial = nullptr;
	onBuiltMaterial = nullptr;
	onPointingOverMaterial = nullptr;

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
	SetCollisionObjectType( BuildingChannel );
}

void ASBuildable::OnBuilt()
{
	ChangeMaterial(onBuiltMaterial);
	currentState = Built;
	SetCollisionObjectType( BuildableChannel );
}

void ASBuildable::OnPointingOver()
{
	ChangeMaterial(onPointingOverMaterial);
	currentState = PointingOver;
	SetCollisionObjectType( BuildableChannel );
}

void ASBuildable::OnDestroy()
{
	this->Destroy();
}

BuildableState ASBuildable::GetCurrentState()
{
	return currentState;
}

void ASBuildable::ChangeMaterial(UMaterial *material)
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes) mesh->SetMaterial(0, material);
}

void ASBuildable::SetCollisionObjectType(ECollisionChannel channel)
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent* mesh : meshes)  mesh->SetCollisionObjectType(channel);
}