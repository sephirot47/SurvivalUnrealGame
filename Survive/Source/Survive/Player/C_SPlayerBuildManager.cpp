#include "Survive.h"
#include "C_SPlayerBuildManager.h"


UC_SPlayerBuildManager::UC_SPlayerBuildManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_SPlayerBuildManager::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ACharacter>(GetOwner());
	character->InputComponent->BindAction("Select Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputSelectBuildable);
	character->InputComponent->BindAction("Remove Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputRemoveBuildable);
}

void UC_SPlayerBuildManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (lastTargetBuildable && lastTargetBuildable != targetBuildable)
	{
		if(lastTargetBuildable->GetCurrentState() != BuildableState::Selected)
			lastTargetBuildable->OnBuilt();
	}

	if (targetBuildable)
	{ 
		if (targetBuildable->GetCurrentState() == BuildableState::Built)
			targetBuildable->OnPointingOver();
	}
}

void UC_SPlayerBuildManager::OnInputSelectBuildable() 
{
	if (targetBuildable)
	{
		targetBuildable->OnSelect();
	}
}

void UC_SPlayerBuildManager::OnInputRemoveBuildable() 
{
}