#include "Survive.h"
#include "C_SPlayerBuildManager.h"


UC_SPlayerBuildManager::UC_SPlayerBuildManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	currentState = PlayerBuildingState::Pointing;
	targetPoint = FVector::ZeroVector;
}


void UC_SPlayerBuildManager::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ACharacter>(GetOwner());
	character->InputComponent->BindAction("Move Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputMoveBuildable);
	character->InputComponent->BindAction("Remove Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputRemoveBuildable);
}

void UC_SPlayerBuildManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (lastTargetBuildable && lastTargetBuildable != targetBuildable)
	{
		lastTargetBuildable->OnBuilt();
	}

	if (targetBuildable)
	{ 
		if (targetBuildable->GetCurrentState() == BuildableState::Built)
			targetBuildable->OnPointingOver();
	}

	if (currentState == PlayerBuildingState::Moving)
	{
		if (targetBuildable)
		{
			GEngine->AddOnScreenDebugMessage(123, 1.0f, FColor::Green, targetPoint.ToString());
			targetBuildable->SetActorLocation( targetPoint );
		}
	}
}

void UC_SPlayerBuildManager::OnInputMoveBuildable()
{
	if (currentState == PlayerBuildingState::Pointing)  //Start moving the buildable
	{
		if (targetBuildable)
		{
			currentState = PlayerBuildingState::Moving;
			targetBuildable->OnBuilding();
		}
	}
	else if (currentState == PlayerBuildingState::Moving) //Finished moving the buildable (confirmed new location)
	{
		if (targetBuildable)
		{
			currentState = PlayerBuildingState::Pointing;
			targetBuildable->OnBuilt();
		}
	}
}

void UC_SPlayerBuildManager::OnInputRemoveBuildable() 
{
	if (targetBuildable)
	{
		targetBuildable->OnDestroy();
	}
}

PlayerBuildingState UC_SPlayerBuildManager::GetCurrentBuildingState()
{
	return currentState;
}