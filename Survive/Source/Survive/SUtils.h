#pragma once

class SURVIVE_API SUtils
{
public:

	static bool Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut);
	static bool Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel TraceChannel);
	static AActor* Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End);
	static AActor* Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel);
};
