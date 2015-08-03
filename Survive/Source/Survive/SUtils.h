#pragma once

#include "InGame/Characters/IDamageReceiver.h"

class SURVIVE_API SUtils
{
public:

	static bool Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut);
	static bool Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel TraceChannel);

	static AActor* Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End);
	static AActor* Trace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel);
	static bool MultiTrace(TArray<AActor*> &actorsToIgnore, const FVector& Start, const FVector& End, TArray<FHitResult>& HitsOut, TArray<AActor*>& actorsHit);

	//Get ALL the Actors of type T in a specified radius from the originActor (sort of an sphere trace around originActor of radius=radius).
	//If the parameter planar is true, then the Z coordinate is not taken into account. If it's false, Z is taken into account.
	//The originActor is not added to the array
	template <class T>
	static void GetAll_InARadiusOf(UWorld *world, AActor *originActor, float radius, TArray<T*>& TFound, bool planar = false)
	{
		TFound.Empty();
		for (TActorIterator<AActor> actor(world); actor; ++actor)
		{
			if (*actor == originActor) continue;

			FVector pos0 = originActor->GetActorLocation(); if(planar) pos0.Z = .0f;
			FVector pos1 = actor->GetActorLocation(); if (planar) pos1.Z = .0f;
			if (FVector::Dist(pos0, pos1) <= radius)
			{
				T *TObject = Cast<T>(*actor);
				if (TObject) TFound.Add(TObject);
			}
		}
	}

	//Get all the Actors in the specified world of type T. They are stored in the array passed by reference
	template <class T>
	static void GetAll(UWorld *world, TArray<T*>& TFound)
	{
		for (TActorIterator<AActor> actor(world); actor; ++actor)
		{
			T *TObject = Cast<T>(*actor);
			if (TObject) TFound.Add(TObject);
		}
	}

	//Get the closest Actor of type T from originActor. If planar==TRUE,  then the Z coord is NOT taken into account. Otherwise, Z is taken into account.
	//The originActor is obviously not taken into account
	template <class T>
	static T* GetClosestTo(UWorld *world,  AActor *originActor, bool planar = false)
	{
		T* closest = nullptr;
		float minDist = -1.0f;
		for (TActorIterator<AActor> actor(world); actor; ++actor)
		{
			if (*actor == originActor) continue;

			FVector pos0 = originActor->GetActorLocation(); if (planar) pos0.Z = .0f;
			FVector pos1 = actor->GetActorLocation(); if (planar) pos1.Z = .0f;
			float dist = FVector::Dist(pos0, pos1);

			if (minDist < 0.0f || dist < minDist)
			{
				T *TObject = Cast<T>(*actor);
				if (TObject)
				{
					closest = TObject;
					minDist = dist;
				}
			}
		}

		return closest;
	}
	
	//Get all the visible Actors of type T from originActor. They are stored in the TFound array passed by reference.
	//If no visionRadius is specified, it's supposed to be infinite. Otherwise, all the found Actors will be inside a radius of size visionRadius.
	//If planar==TRUE,  then the Z coord is NOT taken into account when working with the visionRadius. Otherwise, Z is taken into account.
	//The originActor is obviously not taken into account
	template <class T>
	static void GetVisibleFrom(UWorld *world, AActor *originActor, TArray<T*>& TFound, float visionRadius = -1.0f, bool planar = false)
	{
		for (TActorIterator<AActor> actor(world); actor; ++actor)
		{
			if (*actor == originActor) continue;

			FVector pos0 = originActor->GetActorLocation(); if (planar) pos0.Z = .0f;
			FVector pos1 = actor->GetActorLocation(); if (planar) pos1.Z = .0f;
			float dist = FVector::Dist(pos0, pos1);
			if (visionRadius < 0.0f || dist <= visionRadius)
			{
				TArray<AActor*> ignore; ignore.Add(originActor);

				AActor *hitActor = Trace(ignore, originActor->GetActorLocation(), actor->GetActorLocation());
				if (hitActor == *actor) //If its visible (doesnt hit anything, so the ray really hits the actor)
				{
					T *TObject = Cast<T>(*actor);
					if (TObject)
					{
						TFound.Add(TObject);
					}
				}
			}
		}
	}
};
