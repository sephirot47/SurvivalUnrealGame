#include "Survive.h"
#include "C_SPlayerMovement.h"

UC_SPlayerMovement::UC_SPlayerMovement()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	pitch = 0.0f;
}


void UC_SPlayerMovement::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ASPlayer>(GetOwner());
	arms = player->GetArms();

	//Inputs ////////////////
	GetOwner()->InputComponent->BindAxis("MoveX", this, &UC_SPlayerMovement::HandleMoveX);
	GetOwner()->InputComponent->BindAxis("MoveY", this, &UC_SPlayerMovement::HandleMoveY);
	GetOwner()->InputComponent->BindAxis("TurnX", this, &UC_SPlayerMovement::HandleTurnX);
	GetOwner()->InputComponent->BindAxis("TurnY", this, &UC_SPlayerMovement::HandleTurnY);
	/////////////////////////
}

void UC_SPlayerMovement::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}
void UC_SPlayerMovement::HandleMoveX(float v)
{
	FVector mov = player->GetActorRightVector() * v;
	player->AddMovementInput(mov);
}

void UC_SPlayerMovement::HandleMoveY(float v)
{
	FVector mov = player->GetActorForwardVector() * v;
	player->AddMovementInput(mov);
}

void UC_SPlayerMovement::HandleTurnX(float v)
{
	player->AddControllerYawInput(v);
}

void UC_SPlayerMovement::HandleTurnY(float v)
{
	FVector rot = FVector(0.0f, v, 0.0f);
	if (arms != nullptr) arms->AddRelativeRotation( FQuat::MakeFromEuler(rot) );
}

