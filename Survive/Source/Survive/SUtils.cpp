#include "Survive.h"
#include "SUtils.h"

bool SUtils::Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	HitOut = FHitResult(ForceInit);

	FCollisionObjectQueryParams queryParams;
	TObjectIterator< APlayerController > pc; if (!pc) return false;
	pc->GetWorld()->LineTraceSingleByObjectType(HitOut, Start, End, queryParams, TraceParams);
	return HitOut.GetActor() != nullptr;
}

bool SUtils::Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel TraceChannel)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	HitOut = FHitResult(ForceInit);

	TObjectIterator< APlayerController > pc; if (!pc) return false;
	pc->GetWorld()->LineTraceSingleByChannel(HitOut, Start, End, TraceChannel, TraceParams);
	return HitOut.GetActor() != nullptr;
}

bool SUtils::MultiTrace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, TArray<FHitResult>& HitsOut, TArray<AActor*> actorsHit)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	//HitOut = FHitResult(ForceInit);

	TObjectIterator< APlayerController > pc; if (!pc) return false;

	FCollisionObjectQueryParams queryParams;
	pc->GetWorld()->LineTraceMultiByObjectType(HitsOut, Start, End, queryParams, TraceParams);
	
	GEngine->AddOnScreenDebugMessage(9999, 1.0f, FColor::Blue, FString::FromInt(HitsOut.Num()));
	for (FHitResult hitOut : HitsOut) actorsHit.Add(hitOut.GetActor());
	return actorsHit.Num() >= 1;
}

AActor* SUtils::Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	FHitResult HitOut = FHitResult(ForceInit);

	FCollisionObjectQueryParams queryParams;
	TObjectIterator< APlayerController > pc; if (!pc) return false;
	pc->GetWorld()->LineTraceSingleByObjectType(HitOut, Start, End, queryParams, TraceParams);
	return HitOut.GetActor();
}

AActor* SUtils::Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	FHitResult HitOut = FHitResult(ForceInit);

	TObjectIterator< APlayerController > pc; if (!pc) return false;
	pc->GetWorld()->LineTraceSingleByChannel(HitOut, Start, End, TraceChannel, TraceParams);
	return HitOut.GetActor();
}