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
	player = Cast<ASPlayer>(character);

	FInputActionBinding *toggle;
	toggle = &player->InputComponent->BindAction("Open Buildings Menu", IE_Pressed, this, &ASGameState::OnInput_OpenBuildingsMenu);
	toggle->bExecuteWhenPaused = true;

	toggle = &player->InputComponent->BindAction("Open Inventory", IE_Pressed, this, &ASGameState::OnInput_OpenInventory);
	toggle->bExecuteWhenPaused = true;

	toggle = &player->InputComponent->BindAction("Go Back", IE_Pressed, this, &ASGameState::OnInput_GoBack);
	toggle->bExecuteWhenPaused = true;

	toggle = &player->InputComponent->BindAction("Pause", IE_Pressed, this, &ASGameState::OnInput_PauseGame);
	toggle->bExecuteWhenPaused = true; //EVEN THOUGH THE GAME IS PAUSED, CATCH THIS EVENT !!!! To be able to unpause hehe :)

	SetCurrentGameFlowState(GameFlowState::Playing);
}

void ASGameState::OnInput_OpenBuildingsMenu()
{
	if (currentState != GameFlowState::BuildingsMenu)
	{
		//if (player->GetBuildManager()->GetCurrentBuildingState() != PlayerBuildingState::Moving)
		SetCurrentGameFlowState(GameFlowState::BuildingsMenu);
	}
	else
	{
		SetCurrentGameFlowState(GameFlowState::Playing);
	}
}

void ASGameState::OnInput_OpenInventory()
{
	if (currentState != GameFlowState::Inventory)
	{
		SetCurrentGameFlowState(GameFlowState::Inventory);
	}
	else
	{
		SetCurrentGameFlowState(GameFlowState::Playing);
	}
}

void ASGameState::OnInput_GoBack()
{
	SetCurrentGameFlowState(GameFlowState::Playing);
}

void ASGameState::SetCurrentGameFlowState(GameFlowState state) 
{
	currentState = state;

	if (currentState == GameFlowState::Playing)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

GameFlowState ASGameState::GetCurrentGameFlowState() { return currentState; }

void ASGameState::OnInput_PauseGame()
{
	if (currentState != GameFlowState::Paused)
	{
		SetCurrentGameFlowState(GameFlowState::Paused);
	}
	else
	{
		SetCurrentGameFlowState(GameFlowState::Playing);
	}
}

