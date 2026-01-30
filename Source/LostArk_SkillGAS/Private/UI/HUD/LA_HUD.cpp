#include "UI/HUD/LA_HUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/Player/LA_PlayerHUDWidget.h"


void ALA_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (PlayerHUDWidgetClass)
	{
		PlayerHUDWidget = CreateWidget<ULA_PlayerHUDWidget>(PC, PlayerHUDWidgetClass);
		PlayerHUDWidget->AddToViewport();
		// 초기값 설정및 델리게이트 바인딩
	}
}
