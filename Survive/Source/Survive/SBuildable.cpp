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
	SetCollidableWithPlayer(false);
}

void ASBuildable::OnBuilt()
{
	ChangeMaterial(onBuiltMaterial);
	currentState = Built;
	SetCollidableWithPlayer(true);
}

void ASBuildable::OnPointingOver()
{
	ChangeMaterial(onPointingOverMaterial);
	currentState = PointingOver;
	SetCollidableWithPlayer(true);
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

void ASBuildable::SetCollidableWithPlayer(bool collidableWithPlayer)
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
		mesh->SetCollisionResponseToChannel(ECC_Pawn, collidableWithPlayer ? ECR_Block : ECR_Overlap);
}