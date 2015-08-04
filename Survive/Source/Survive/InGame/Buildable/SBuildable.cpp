#include "Survive.h"
#include "SBuildable.h"

ASBuildable::ASBuildable()
{
	PrimaryActorTick.bCanEverTick = true;

	currentState = Built;
	rotationSpeed = -3.0f;

	maxLife = 100.0f;
	life = maxLife;
}

void ASBuildable::BeginPlay()
{
	Super::BeginPlay();
	ChangeMaterial(BuildableMaterial::BuiltMaterial);
}

void ASBuildable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (life <= 0.0f)
	{
		this->Destroy();
		OnDestroy();
	}
	else
	{
		if (currentState == BuildableState::Building)
		{
			TArray<AActor*> overlaps;
			GetOverlappingActors(overlaps);
			isOverlapping = overlaps.Num() >= 1;

			if (isOverlapping) ChangeMaterial(BuildableMaterial::WrongBuildingMaterial);
			else ChangeMaterial(BuildableMaterial::BuildingMaterial);
		}
	}
}


void ASBuildable::OnBuilding_Implementation()
{
	ChangeMaterial(BuildableMaterial::BuildingMaterial);
	currentState = Building;
	SetCollidableWithPlayer(false);
}

void ASBuildable::OnBuilt_Implementation()
{
	BuildableState lastState = currentState;

	ChangeMaterial(BuildableMaterial::BuiltMaterial);
	currentState = Built;
	SetCollidableWithPlayer(true);
}

void ASBuildable::OnPointingOver_Implementation()
{
	ChangeMaterial(BuildableMaterial::PointingOverMaterial);
	currentState = PointingOver;
	SetCollidableWithPlayer(true);
}

void ASBuildable::OnDestroy_Implementation()
{
	this->Destroy();
}

BuildableState ASBuildable::GetCurrentState()
{
	return currentState;
}

FLinearColor ASBuildable::GetCurrentMaterialColor()
{
	FLinearColor color;

	if (currentMaterial == BuildableMaterial::BuildingMaterial) color = FLinearColor(colorBuildingMaterial);
	else if (currentMaterial == BuildableMaterial::WrongBuildingMaterial) color = FLinearColor(colorWrongBuildingMaterial);
	else if (currentMaterial == BuildableMaterial::BuiltMaterial) color = FLinearColor(colorBuiltMaterial);
	else if (currentMaterial == BuildableMaterial::PointingOverMaterial) color = FLinearColor(colorPointingOverMaterial);
	else if (currentMaterial == BuildableMaterial::SelectedMaterial) color = FLinearColor(colorSelectedMaterial);

	//Apply damage reddish color
	color = FLinearColor::LerpUsingHSV(color, FLinearColor::Red, (1.0f - life / maxLife));

	return color;
}

void ASBuildable::ChangeMaterial(BuildableMaterial material)
{
	if (currentMaterial == material) return;

	currentMaterial = material;
	ApplyCurrentMaterialColors();
}

void ASBuildable::ApplyCurrentMaterialColors()
{
	bool translucent = (currentMaterial == BuildableMaterial::WrongBuildingMaterial || currentMaterial == BuildableMaterial::BuildingMaterial);

	FLinearColor color = GetCurrentMaterialColor();
	dynamicMaterialOpaque->SetVectorParameterValue(TEXT("BaseColor"), color);
	dynamicMaterialTranslucent->SetVectorParameterValue(TEXT("BaseColor"), color);

	TArray<UMeshComponent*> meshes; GetComponents<UMeshComponent>(meshes);
	for (UMeshComponent *mesh : meshes)
		for (int i = 0; i < mesh->GetNumMaterials(); ++i)
			mesh->SetMaterial(i, translucent ? dynamicMaterialTranslucent : dynamicMaterialOpaque);
}

void ASBuildable::SetCollidableWithPlayer(bool collidableWithPlayer)
{
	TArray<UMeshComponent*> meshes;
	GetComponents<UMeshComponent>(meshes);
	for (UMeshComponent *mesh : meshes)
		mesh->SetCollisionResponseToChannel(ECC_Pawn, collidableWithPlayer ? ECR_Block : ECR_Overlap);

	for (UMeshComponent *mesh : meshes)
		mesh->SetCanEverAffectNavigation(collidableWithPlayer);
}

void ASBuildable::OnOutOfPlayerBuildRange()
{
	ChangeMaterial(WrongBuildingMaterial);
}

void ASBuildable::OnInsideOfPlayerBuildRange()
{
	ChangeMaterial(BuildingMaterial);
}

void ASBuildable::ReceiveDamage(AActor* originActor, float damage)
{
	life -= damage;
	OnReceiveDamage(originActor, damage);
}

void ASBuildable::OnReceiveDamage_Implementation(AActor* originActor, float damage)
{
	ApplyCurrentMaterialColors();
}