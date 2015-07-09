#include "Survive.h"
#include "SHUD.h"

ASHUD::ASHUD()
{
	crosshairTexture = nullptr;
	crosshairScale = 0.1f;
}

void ASHUD::DrawHUD()
{
	Super::DrawHUD();
	if(crosshairTexture) DrawInCenter(crosshairTexture, crosshairScale);
}

void ASHUD::DrawInCenter(const UTexture2D *texture, float scale)
{
	const FVector2D screenSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D screenCenter = FVector2D(screenSize.X / 2, screenSize.Y / 2);
	const FVector2D p = FVector2D(screenCenter.X - texture->GetSurfaceWidth() * 0.5f * scale, 
								  screenCenter.Y - texture->GetSurfaceHeight() * 0.5f * scale);

	DrawTextureSimple(crosshairTexture, p.X, p.Y, scale);
}




