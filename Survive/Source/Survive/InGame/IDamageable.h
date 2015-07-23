#pragma once

#include "IDamageable.generated.h"

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageable
{
	GENERATED_IINTERFACE_BODY()

		virtual void ReceiveAttack();
};