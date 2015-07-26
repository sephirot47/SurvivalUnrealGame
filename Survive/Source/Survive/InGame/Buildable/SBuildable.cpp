#include "Survive.h"
#include "SBuildable.h"

ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;

	lastMaterial = nullptr;

	currentState = Built;
	overlaps = 0;
	rotationSpeed = -3.0f;

	maxLife = 100.0f;
	life = maxLife;
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

	if (life <= 0.0f)
	{
		//this->Destroy();
		OnDestroy(); //Fix: destroy after a bit of time has passed
	}
}


void ASBuildable::OnBuilding_Implementation()
{
	ChangeMaterial(onBuildingMaterial);
	currentState = Building;
	SetCollidableWithPlayer(false);
}

void ASBuildable::OnBuilt_Implementation()
{
	BuildableState lastState = currentState;

	ChangeMaterial(onBuiltMaterial);
	currentState = Built;
	SetCollidableWithPlayer(true);
}

void ASBuildable::OnPointingOver_Implementation()
{
	ChangeMaterial(onPointingOverMaterial);
	currentState = PointingOver;
	SetCollidableWithPlayer(true);
}

void ASBuildable::OnDestroy_Implementation()
{
}

BuildableState ASBuildable::GetCurrentState()
{
	return currentState;
}

void ASBuildable::ChangeMaterial(UMaterial *material)
{
	TArray<UMeshComponent*> meshes;
	GetComponents<UMeshComponent>(meshes);

	if (meshes.Num() > 0) lastMaterial = meshes[0]->GetMaterial(0)->GetMaterial();
	for (UMeshComponent *mesh : meshes)
	{
		for (int i = 0; i < mesh->GetNumMaterials(); ++i) mesh->SetMaterial(i, material);
	}
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

void ASBuildable::ReceiveDamage(AActor* originActor, float damage)
{
	life -= damage;
	OnReceiveDamage(originActor, damage);
}

void ASBuildable::OnReceiveDamage_Implementation(AActor* originActor, float damage)
{

}