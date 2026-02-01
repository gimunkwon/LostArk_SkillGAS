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

void ALA_HUD::ShowContextMenu()
{
	if (!ContextMenuClass) return;
	
	HideContextMenu(); // 기존 메뉴가 있다면 제거
	
	ContextMenuWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), ContextMenuClass);
	if (ContextMenuWidget)
	{
		ContextMenuWidget->AddToViewport();
		
		// 마우스 위치 계산 및 배치
		float MouseX, MouseY;
		GetOwningPlayerController()->GetMousePosition(MouseX, MouseY);
		ContextMenuWidget->SetPositionInViewport(FVector2D(MouseX, MouseY));
	}
}

void ALA_HUD::HideContextMenu()
{
	if (ContextMenuWidget)
	{
		ContextMenuWidget->RemoveFromParent();
		ContextMenuWidget = nullptr;
	}
}
