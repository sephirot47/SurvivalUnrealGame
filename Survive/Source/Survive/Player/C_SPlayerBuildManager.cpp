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
			GEngine->AddOnScreenDebugMessage(123, 1.0f, FColor::Green, targetPoint.ToString());
			targetBuildable->SetActorLocation( targetPoint );
		}
	}
}

void UC_SPlayerBuildManager::FillTargetInfo()
{
	TArray<AActor*> ignoredActors;
	ignoredActors.Add(GetOwner()); //Ignore myself

	FVector traceStart = character->GetActorLocation();
	FVector traceEnd   = traceStart + character->GetActorForwardVector() * 9999.9f;

	ECollisionChannel channel;
	if (currentState == PlayerBuildingState::Pointing) channel = BuildableChannel;
	else channel = ECC_WorldStatic;

	FHitResult hitResult;
	if (Trace(ignoredActors, traceStart, traceEnd, hitResult, channel))
	{
		targetPoint = hitResult.Location;

		//Only when Pointing. If we are Moving, we must not override targetBuildable 
		if (currentState == PlayerBuildingState::Pointing)
		{
			ASBuildable *buildable = Cast<ASBuildable>(hitResult.GetActor());
			targetBuildable = buildable; //If the hit object is not a buildable, then the cast fails, hence buildable = nullptr :)
		}
	}
	else
	{
		targetPoint = FVector::ZeroVector;

		//Only put it to nullptr when player is Pointing, because if it's Moving we must keep a reference
		//to the moving buildable in targetBuildable variable, in order to be able to move this
		if (currentState == PlayerBuildingState::Pointing)  
			targetBuildable = nullptr; 
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


FORCEINLINE bool UC_SPlayerBuildManager::Trace(TArray<AActor*> &actorsToIgnore,
												const FVector& Start, const FVector& End, FHitResult& HitOut,
												ECollisionChannel CollisionChannel)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	HitOut = FHitResult(ForceInit);

	TObjectIterator< APlayerController > ThePC;
	if (!ThePC) return false;

	ThePC->GetWorld()->LineTraceSingle(HitOut, Start, End, CollisionChannel, TraceParams);
	return (HitOut.GetActor() != NULL);
}