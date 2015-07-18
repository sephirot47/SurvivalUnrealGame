#include "Survive.h"
#include "C_SPlayerBuildManager.h"


UC_SPlayerBuildManager::UC_SPlayerBuildManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	currentState = PlayerBuildingState::Pointing;
	targetPoint = FVector::ZeroVector;

	rotateInputDown = false;
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
	FillTargetInfo(); //Fill targetBuildable and targetPoint variables

	if (lastTargetBuildable && 
		lastTargetBuildable != targetBuildable)
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
			targetBuildable->SetActorLocation( targetPoint );
		}
	}

	if (rotateInputDown) RotateTargetBuildable();
}

void UC_SPlayerBuildManager::FillTargetInfo()
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(GetOwner()); //Ignore myself (he player)

	APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector traceStart = camManager->GetCameraLocation();
	FVector traceEnd = traceStart + camManager->GetCameraRotation().Vector() * 9999.9f;
	//DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, true, 1.0f);

	ECollisionChannel channel;
	if (currentState == PlayerBuildingState::Pointing) channel = PlayerPointingTraceChannel;
	else channel = PlayerMovingTraceChannel;

	FHitResult hitResult;
	if (Trace(ignoredActors, traceStart, traceEnd, hitResult, channel)) 
	{
		//Hitting something!
		targetPoint = hitResult.Location;

		//Only when Pointing. If we are Moving, we must not override targetBuildable 
		if (currentState == PlayerBuildingState::Pointing)
		{
			ASBuildable *buildable = Cast<ASBuildable>(hitResult.GetActor());
			targetBuildable = buildable; //If the hit object is not a buildable, then the cast fails, hence buildable = nullptr :)
		}

		if (targetBuildable) targetBuildable->SetActorHiddenInGame(false);
	}
	else //Don't hit anything
	{
		targetPoint = FVector::ZeroVector;

		if (currentState == PlayerBuildingState::Pointing)  targetBuildable = nullptr;
		if (currentState == PlayerBuildingState::Moving && targetBuildable) targetBuildable->SetActorHiddenInGame(true);
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
		//Si tiene targetBuildable y esta apuntando a algun sitio donde pueda ponerlo...
		if (targetBuildable && targetPoint != FVector::ZeroVector)
		{
			if (targetBuildable->CanBeBuilt())
			{
				currentState = PlayerBuildingState::Pointing;
				targetBuildable->OnBuilt();
			}
		}
	}
}

//This function adds the left click input for when you want to put the buildable, but not for moving it
void UC_SPlayerBuildManager::OnInputPutBuildable()
{
	OnInputMoveBuildable();
}

void UC_SPlayerBuildManager::OnInputRotateBuildableDown() { rotateInputDown = true; }
void UC_SPlayerBuildManager::OnInputRotateBuildableUp() { rotateInputDown = false; }

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
	if (targetBuildable && targetPoint != FVector::ZeroVector)
	{
		targetBuildable->OnDestroy();
		currentState = PlayerBuildingState::Pointing;
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
	currentState = PlayerBuildingState::Moving;
}

PlayerBuildingState UC_SPlayerBuildManager::GetCurrentBuildingState()
{
	return currentState;
}


FORCEINLINE bool UC_SPlayerBuildManager::Trace(TArray<AActor*> &actorsToIgnore,
												const FVector& Start, const FVector& End, FHitResult& HitOut,
												ECollisionChannel TraceChannel)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	HitOut = FHitResult(ForceInit);

	TObjectIterator< APlayerController > pc;
	if (!pc) return false;

	pc->GetWorld()->LineTraceSingleByChannel(HitOut, Start, End, TraceChannel, TraceParams);
	return (HitOut.GetActor() != NULL);
}