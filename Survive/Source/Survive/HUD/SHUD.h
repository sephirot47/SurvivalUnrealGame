#pragma once

#include "GameFramework/HUD.h"
#include "SHUD.generated.h"

UCLASS()
class SURVIVE_API ASHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = HUDCrosshair) UTexture2D *crosshairTexture;
	UPROPERTY(EditAnywhere, Category = HUDCrosshair) float crosshairScale;

public:
	ASHUD();
	virtual void DrawHUD() override;

	void DrawInCenter(const UTexture2D *texture, float scale = 1.0f);
};
