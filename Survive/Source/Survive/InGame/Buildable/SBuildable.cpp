#include "Survive.h"
#include "SBuildable.h"

ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;

	lastMaterial = nullptr;

	currentState = Built;
	overlaps = 0;
	rotationSpeed = -3.0f;
}

void ASBuildable::BeginPlay()
{
	Super::BeginPlay();

	//Register overlap functions
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
	{
		mesh->OnComponentBeginOverlap.AddDynamic(this, &ASBuildable::OnBeginOverlap);
		mesh->OnComponentEndOverlap.AddDynamic(this, &ASBuildable::OnEndOverlap);
	}
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
	BuildableState lastState = currentState;

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

	if (meshes.Num() > 0) lastMaterial = meshes[0]->GetMaterial(0)->GetMaterial();
	for (UStaticMeshComponent *mesh : meshes) mesh->SetMaterial(0, material);
}

void ASBuildable::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								 bool bFromSweep, const FHitResult & SweepResult)
{
	++overlaps;
	if (overlaps == 1 && currentState == Building) ChangeMaterial(onWrongBuildingMaterial);
}

void ASBuildable::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	--overlaps;
	if (overlaps == 0 && currentState == Building) ChangeMaterial(onBuildingMaterial);
}


void ASBuildable::SetCollidableWithPlayer(bool collidableWithPlayer)
{
	TArray<UStaticMeshComponent*> meshes;
	GetComponents<UStaticMeshComponent>(meshes);
	for (UStaticMeshComponent *mesh : meshes)
		mesh->SetCollisionResponseToChannel(ECC_Pawn, collidableWithPlayer ? ECR_Block : ECR_Overlap);
}

void ASBuildable::AddWaypointsToArray(TArray<FVector>& wpArray)
{
	TArray<AActor*> children;
	this->GetAttachedActors(children);
	for (int i = 0; i < children.Num(); ++i)
	{
		AActor* child = children[i];
		ATargetPoint *waypoint = Cast<ATargetPoint>(child);
		if (waypoint) wpArray.Add(waypoint->GetActorLocation());
	}
}