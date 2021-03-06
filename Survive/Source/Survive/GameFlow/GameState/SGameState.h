#pragma once

#include "../../InGame/Characters/Player/SPlayer.h"
#include "GameFramework/GameState.h"
#include "SGameState.generated.h"

UENUM(BlueprintType)
enum GameFlowState
{
	Playing,
	Inventory,
	Paused
};

UCLASS()
class SURVIVE_API ASGameState : public AGameState
{
	GENERATED_BODY()

private:
	GameFlowState currentState;
	ASPlayer *player;

	void OnInput_OpenInventory();
	void OnInput_GoBack();
	void OnInput_PauseGame();

public:

	ASGameState();

	virtual void BeginPlay() override;

	void SetState(GameFlowState state);

	UFUNCTION(BlueprintCallable, Category = "Game Flow State")
		void SetCurrentGameFlowState(GameFlowState state);

	UFUNCTION(BlueprintCallable, Category = "Game Flow State")
		GameFlowState GetCurrentGameFlowState();
};
