#include "Survive.h"
#include "SGameState.h"

ASGameState::ASGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASGameState::BeginPlay()
{
	Super::BeginPlay();

	ACharacter *character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	character->InputComponent->BindAction("Open Buildings Menu", IE_Pressed, this, &ASGameState::OnInput_OpenBuildingsMenu);
	character->InputComponent->BindAction("Open Inventory", IE_Pressed, this, &ASGameState::OnInput_OpenInventory);
	character->InputComponent->BindAction("Go Back", IE_Pressed, this, &ASGameState::OnInput_GoBack);
}

void ASGameState::OnInput_OpenBuildingsMenu()
{
	if (currentState == GameFlowState::BuildingsMenu) currentState = GameFlowState::Playing;
	else currentState = GameFlowState::BuildingsMenu;
}

void ASGameState::OnInput_OpenInventory()
{
	if (currentState == GameFlowState::Inventory) currentState = GameFlowState::Playing;
	else currentState = GameFlowState::Inventory;
}

void ASGameState::OnInput_GoBack()
{
	currentState = GameFlowState::Playing;
}

void ASGameState::SetCurrentGameFlowState(GameFlowState state) { currentState = state; }
GameFlowState ASGameState::GetCurrentGameFlowState() { return currentState; }


