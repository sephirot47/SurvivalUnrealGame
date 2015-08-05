#include "Survive.h"
#include "SWeapon.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	timeLastShot = 999.9f;
	rateOfFire = 3.0f;

	damage = 5.0f;
	weight = 0.1f;

	usingWeapon = false;
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ASPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	player->InputComponent->BindAction("Weapon Use", IE_Pressed, this, &ASWeapon::OnWeaponUseInput);
	player->InputComponent->BindAction("Weapon Use", IE_Released, this, &ASWeapon::OnWeaponUnUseInput);
}

void ASWeapon::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	timeLastShot += DeltaTime;
	if (usingWeapon) Use();
}

bool ASWeapon::CanBeUsed()
{
	return !WaitingForRateOfFire();
}

void ASWeapon::Use()
{
}

float ASWeapon::GetRateOfFire()
{
	return rateOfFire;
}

bool ASWeapon::WaitingForRateOfFire()
{
	return timeLastShot < 1.0f / rateOfFire;
}
