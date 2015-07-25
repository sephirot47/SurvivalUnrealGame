#pragma once

#include "GameFramework/Actor.h"
#include "IDamageReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UDamageReceiver : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IDamageReceiver
{
	GENERATED_IINTERFACE_BODY()

	virtual void ReceiveDamage(AActor* originActor, float damage);
};