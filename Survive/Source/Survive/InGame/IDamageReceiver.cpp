#include "Survive.h"
#include "IDamageReceiver.h"

void IDamageReceiver::ReceiveDamage(AActor* originActor, float damage)
{
}

UDamageReceiver::UDamageReceiver(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}