#pragma once

#include "GameFramework/GameState.h"
#include "SGameState.generated.h"

UENUM(BlueprintType)
enum GameFlowState
{
	Playing,
	BuildingsMenu,
	Inventory,
	Paused
};

UCLASS()
class SURVIVE_API ASGameState : public AGameState
{
	GENERATED_BODY()
	
private:
	GameFlowState currentState;

	void OnInput_OpenBuildingsMenu();
	void OnInput_OpenInventory();
	void OnInput_GoBack();
	void OnInput_PauseGame();

public:

	ASGameState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Game Flow State")
		void SetCurrentGameFlowState(GameFlowState state);

	UFUNCTION(BlueprintCallable, Category = "Game Flow State")
		GameFlowState GetCurrentGameFlowState();
};
