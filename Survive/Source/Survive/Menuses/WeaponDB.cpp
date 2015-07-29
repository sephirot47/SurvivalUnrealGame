#include "Survive.h"
#include "WeaponDB.h"

AWeaponDB::AWeaponDB()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponDB::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponDB::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

