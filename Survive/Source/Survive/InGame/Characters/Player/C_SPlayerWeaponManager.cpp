#include "Survive.h"
#include "C_SPlayerWeaponManager.h"

UC_SPlayerWeaponManager::UC_SPlayerWeaponManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_SPlayerWeaponManager::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ASPlayer>(GetOwner());
}


void UC_SPlayerWeaponManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UC_SPlayerWeaponManager::EquipWeapon(ASWeapon *weapon)
{
	currentWeapon = weapon;
	weapon->AttachRootComponentTo(player->GetSKMannequin(), weaponSocketName);
	player->MoveIgnoreActorAdd(currentWeapon);
}

void UC_SPlayerWeaponManager::UnEquipCurrentWeapon()
{
	if (currentWeapon)
	{
		currentWeapon->Destroy();
		currentWeapon = nullptr;
	}
}

void UC_SPlayerWeaponManager::OnWeaponsMenuItemSelected(TSubclassOf<ASWeapon> WeaponClass)
{
	UnEquipCurrentWeapon(); //Unequip if another weapon was equiped

	AActor *actor = GetWorld()->SpawnActor(WeaponClass);
	ASWeapon *weapon = Cast<ASWeapon>(actor);
	EquipWeapon(weapon);
}