#include "Survive.h"
#include "SWeapon.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

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
	if (usingWeapon) Use();
}

void ASWeapon::Use()
{
}