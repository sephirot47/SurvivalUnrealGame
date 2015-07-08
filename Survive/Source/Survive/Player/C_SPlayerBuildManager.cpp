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
			currentState = PlayerBuildingState::Pointing;
			targetBuildable->OnBuilt();
		}
	}
}

void UC_SPlayerBuildManager::OnInputRemoveBuildable() 
{
	if (targetBuildable && targetPoint != FVector::ZeroVector)
	{
		targetBuildable->OnDestroy();
	}
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