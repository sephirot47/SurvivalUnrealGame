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
	SetCollisionObjectType( FName("Building") );
}

void ASBuildable::OnBuilt()
{
	ChangeMaterial(onBuiltMaterial);
	currentState = Built;
	SetCollisionObjectType( FName("Buildable") );
}

void ASBuildable::OnPointingOver()
{
	ChangeMaterial(onPointingOverMaterial);
	currentState = PointingOver;
	SetCollisionObjectType( FName("Buildable") );
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
	for (UStaticMeshComponent *mesh : meshes)
		mesh->SetMaterial(0, material);
}

void ASBuildable::SetCollisionObjectType( FName collisionProfileName )
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent* mesh : meshes)
	{
		mesh->SetCollisionProfileName(collisionProfileName);
		mesh->UpdateCollisionProfile();
	}
}