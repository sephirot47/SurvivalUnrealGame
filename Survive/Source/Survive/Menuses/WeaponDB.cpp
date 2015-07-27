#include "Survive.h"
#include "WeaponDB.h"

AWeaponDB::AWeaponDB()
{
	PrimaryActorTick.bCanEverTick = true;
}

TSubclassOf<ASWeapon> AWeaponDB::GetWeaponClassFromId(int32 id)
{
	for (int i = 0; i < weaponItems.Num(); ++i)
	{
		if (weaponItems[i].id == id)
		{
			return weaponItems[i].weaponClass;
		}
	}

	return nullptr;
}

void AWeaponDB::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponDB::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

