#pragma once

#include "GameFramework/HUD.h"
#include "SHUD.generated.h"

UCLASS()
class SURVIVE_API ASHUD : public AHUD
{
	GENERATED_BODY()

private:

public:
	ASHUD();
	virtual void DrawHUD() override;

	void DrawInCenter(UTexture *texture, float scale = 1.0f);
};
