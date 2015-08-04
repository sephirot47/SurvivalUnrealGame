#include "Survive.h"
#include "C_SPlayerBuildManager.h"


UC_SPlayerBuildManager::UC_SPlayerBuildManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	currentState = PlayerBuildingState::PointingBuildable;
	targetPoint = FVector::ZeroVector;

	rotateInputDown = false;
	buildableSelectionRange = 500.0f;
}


void UC_SPlayerBuildManager::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ACharacter>(GetOwner());
	character->InputComponent->BindAction("Move Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputMoveBuildable);
	character->InputComponent->BindAction("Put Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputPutBuildable);
	character->InputComponent->BindAction("Rotate Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputRotateBuildableDown);
	character->InputComponent->BindAction("Rotate Buildable", IE_Released, this, &UC_SPlayerBuildManager::OnInputRotateBuildableUp);
	character->InputComponent->BindAction("Remove Buildable", IE_Pressed, this, &UC_SPlayerBuildManager::OnInputRemoveBuildable);
}

void UC_SPlayerBuildManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	lastTargetBuildable = targetBuildable;
	FillTargetBuildableInfo(); //Fill targetBuildable and targetPoint variables

	if (lastTargetBuildable && 
		lastTargetBuildable != targetBuildable) //The buildable we were pointing isn't pointed anymore. Has to go from OnPointingOver to OnBuilt 
	{
		lastTargetBuildable->OnBuilt();
	}

	if ( targetBuildable && BuildableInRange(targetBuildable) ) //While pointing over a targetBuildable...
	{
		if (targetBuildable->GetCurrentState() == BuildableState::Built) //If it's the first frame we point to a buildable...
			targetBuildable->OnPointingOver();
	}

	if (currentState == PlayerBuildingState::MovingBuildable) //We are moving a buildable
	{
		if (targetBuildable) 
		{
			targetBuildable->SetActorLocation(targetPoint); //Move the buildable
			if ( !BuildableInRange(targetPoint) )
			{
				//If it's not in range, notify the buildable, so it can do whatever it seems to it (aka coloring to red(wrong position))
				targetBuildable->OnOutOfPlayerBuildRange();
			}
			else
			{
				//Otherwise, notify it too (the buildable will change its color to green)
				targetBuildable->OnInsideOfPlayerBuildRange();
			}
		}
	}
	else if (currentState == PlayerBuildingState::PointingBuildable)
	{
		if (targetBuildable && !BuildableInRange(targetBuildable)) 
			targetBuildable->OnBuilt();
	}

	if (rotateInputDown) RotateTargetBuildable();
}

void UC_SPlayerBuildManager::FillTargetBuildableInfo()
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(GetOwner()); //Ignore myself (the player)

	APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector traceStart = camManager->GetCameraLocation();
	FVector traceEnd = traceStart + camManager->GetCameraRotation().Vector() * 99999.9f;
	//DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, true, 1.0f);

	ECollisionChannel channel;
	if (currentState == PlayerBuildingState::PointingBuildable) channel = PlayerPointingTraceChannel;
	else channel = PlayerMovingTraceChannel;

	FHitResult hitResult;
	if ( SUtils::Trace(ignoredActors, traceStart, traceEnd, hitResult, channel) ) 
	{
		//Hitting something!
		targetPoint = hitResult.Location;

		//Only when Pointing. If we are Moving, we must not override targetBuildable 
		if (currentState == PlayerBuildingState::PointingBuildable)
		{
			ASBuildable *buildable = Cast<ASBuildable>(hitResult.GetActor());
			targetBuildable = buildable; //If the hit object is not a buildable, then the cast fails, hence buildable = nullptr :)
		}

		if (targetBuildable) targetBuildable->SetActorHiddenInGame(false);
	}
	else //Don't hit anything
	{
		targetPoint = FVector::ZeroVector;

		if (currentState == PlayerBuildingState::PointingBuildable)  targetBuildable = nullptr;
		if (currentState == PlayerBuildingState::MovingBuildable && targetBuildable) targetBuildable->SetActorHiddenInGame(true);
	}
}

void UC_SPlayerBuildManager::OnInputMoveBuildable()
{
	if (!targetBuildable || !BuildableInRange(targetBuildable)) return;

	if (currentState == PlayerBuildingState::PointingBuildable)  //Start moving the buildable
	{
		if (targetBuildable)
		{
			currentState = PlayerBuildingState::MovingBuildable;
			targetBuildable->OnBuilding();
		}
	}
	else if (currentState == PlayerBuildingState::MovingBuildable) //Finished moving the buildable (confirmed new location)
	{
		//Si tiene targetBuildable y esta apuntando a algun sitio donde pueda ponerlo...
		if (targetBuildable && targetPoint != FVector::ZeroVector)
		{
			if (targetBuildable->CanBeBuilt())
			{
				currentState = PlayerBuildingState::PointingBuildable;
				targetBuildable->OnBuilt();
				rotateInputDown = false;
			}
		}
	}
}

bool UC_SPlayerBuildManager::BuildableInRange(const FVector &buildableLocation)
{
	return FVector::Dist(character->GetActorLocation(), buildableLocation) <= buildableSelectionRange;
}

bool UC_SPlayerBuildManager::BuildableInRange(ASBuildable *buildable)
{
	return BuildableInRange(buildable->GetActorLocation());
}

//This function adds the left click input for when you want to put the buildable, but not for moving it
void UC_SPlayerBuildManager::OnInputPutBuildable()
{
	if (currentState == PlayerBuildingState::MovingBuildable) OnInputMoveBuildable();
}

void UC_SPlayerBuildManager::OnInputRotateBuildableDown() 
{
	if (currentState == PlayerBuildingState::MovingBuildable) rotateInputDown = true;
}
void UC_SPlayerBuildManager::OnInputRotateBuildableUp() 
{
	rotateInputDown = false;
}

void UC_SPlayerBuildManager::RotateTargetBuildable()
{
	if (targetBuildable && rotateInputDown)
	{
		FRotator rot;
		float rotSpeed = targetBuildable->GetRotationSpeed();
		FVector euler(0.0f, 0.0f, rotSpeed);
		rot.MakeFromEuler(euler);
		targetBuildable->AddActorWorldRotation(rot);
	}
}

void UC_SPlayerBuildManager::OnInputRemoveBuildable() 
{
	if (targetBuildable && targetPoint != FVector::ZeroVector && currentState == PlayerBuildingState::MovingBuildable)
	{
		targetBuildable->OnDestroy();
		currentState = PlayerBuildingState::PointingBuildable;
	}
}

void UC_SPlayerBuildManager::OnBuildingsMenuItemSelected(TSubclassOf<ASBuildable> BuildableClass)
{
	AActor *actor = GetWorld()->SpawnActor(BuildableClass);
	ASBuildable *buildable = Cast<ASBuildable>(actor);
	
	//If the player was pointing any building, build it (quit the onpointing)
	//(it will never be built in a wrong place because you can only enter the building menu if the player
	// wasnt moving any buildable)
	if (targetBuildable)  targetBuildable->OnBuilt();

	targetBuildable = buildable;
	targetBuildable->OnBuilding();
	currentState = PlayerBuildingState::MovingBuildable;
}

PlayerBuildingState UC_SPlayerBuildManager::GetCurrentBuildingState()
{
	return currentState;
}