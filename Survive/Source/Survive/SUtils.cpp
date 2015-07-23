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
	pc->GetWorld()->LineTraceSingle(HitOut, Start, End, TraceParams, queryParams);
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


AActor* SUtils::Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End)
{
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
	TraceParams.bTraceComplex = false; //En principio, colliders simples
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActors(actorsToIgnore);
	FHitResult HitOut = FHitResult(ForceInit);

	FCollisionObjectQueryParams queryParams;
	TObjectIterator< APlayerController > pc; if (!pc) return false;
	pc->GetWorld()->LineTraceSingle(HitOut, Start, End, TraceParams, queryParams);
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