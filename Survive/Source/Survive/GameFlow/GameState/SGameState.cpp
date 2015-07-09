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

	FInputActionBinding& toggle = character->InputComponent->BindAction("Pause", IE_Pressed, this, &ASGameState::OnInput_PauseGame);
	toggle.bExecuteWhenPaused = true; //EVEN THOUGH THE GAME IS PAUSED, CATCH THIS EVENT !!!! To be able to unpause hehe :)
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

void ASGameState::OnInput_PauseGame()
{
	if (currentState == GameFlowState::Playing)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		currentState = GameFlowState::Paused;
	}
	else if (currentState == GameFlowState::Paused)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		currentState = GameFlowState::Playing;
	}
}

