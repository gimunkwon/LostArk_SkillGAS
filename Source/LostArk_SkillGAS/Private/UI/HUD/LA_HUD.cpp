#include "UI/HUD/LA_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Controller/Player/LA_PlayerController.h"
#include "UI/Widget/Player/LA_PlayerHUDWidget.h"
#include "UI/Widget/Player/Party/LA_ContextMenuWidget.h"
#include "UI/Widget/Player/Party/LA_InvitePopupWidget.h"
#include "UI/Widget/Player/Party/LA_PartyWidget.h"
#include "UI/Widget/Player/Skill/LA_SkillWidget.h"


void ALA_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (PlayerHUDWidgetClass)
	{
		PlayerHUDWidget = CreateWidget<ULA_PlayerHUDWidget>(PC, PlayerHUDWidgetClass);
		PlayerHUDWidget->AddToViewport();
		// 초기값 설정및 델리게이트 바인딩
	}
}

void ALA_HUD::ShowContextMenu(ALA_BaseCharacter* TargetPlayer)
{
	if (!ContextMenuClass) return;
	
	HideContextMenu(); // 기존 메뉴가 있다면 제거
	
	ContextMenuWidget = CreateWidget<ULA_ContextMenuWidget>(GetOwningPlayerController(), ContextMenuClass);
	if (ContextMenuWidget)
	{
		ContextMenuWidget->AddToViewport();
		
		// 마우스 위치 계산 및 배치
		float MouseX, MouseY;
		GetOwningPlayerController()->GetMousePosition(MouseX, MouseY);
		ContextMenuWidget->SetPositionInViewport(FVector2D(MouseX, MouseY));
		
		ContextMenuWidget->SetTargetCharacter(TargetPlayer);
		
		ContextMenuWidget->OnInviteRequested.AddDynamic(this, &ALA_HUD::HandleInviteRequest);
	}
}

void ALA_HUD::HideContextMenu()
{
	if (ContextMenuWidget)
	{
		ContextMenuWidget->RemoveFromParent();
		ContextMenuWidget->SetTargetCharacter(nullptr);
		ContextMenuWidget = nullptr;
	}
}

void ALA_HUD::HandleInviteRequest(ALA_BaseCharacter* Target)
{
	if (ALA_PlayerController* PC = Cast<ALA_PlayerController>(GetOwningPlayerController()))
	{
		PC->Server_SendPartyInvite(Target);
	}
}

void ALA_HUD::ShowInvitePopUp(ALA_BaseCharacter* Inviter)
{
	if (!InvitePopupClass || !Inviter) return;
	
	// 팝업 생성 및 Inviter 정보 전달
	auto* Popup = CreateWidget<ULA_InvitePopupWidget>(GetOwningPlayerController(), InvitePopupClass);
	if (Popup)
	{
		Popup->InviterCharacter = Inviter;
		Popup->AddToViewport();
	}
	
}

void ALA_HUD::ShowPartyWidget()
{
	if (PartyWidgetClass)
	{
		if (!PartyWidget)
		{
			PartyWidget = CreateWidget<ULA_PartyWidget>(GetOwningPlayerController(), PartyWidgetClass);
		}
		
		if (PartyWidget && !PartyWidget->IsInViewport())
		{
			PartyWidget->AddToViewport();
			
			// 데이터 갱신 시작
			PartyWidget->RefreshPartyList();
			FTimerHandle RefreshTimer;
			GetWorld()->GetTimerManager().SetTimer(RefreshTimer, [this]()
			{
				if (PartyWidget) PartyWidget->RefreshPartyList();
			},0.1f,false);
		}
	}
}

void ALA_HUD::ToggleSkillWidget()
{
	if (SkillWidgetClass)
	{
		if (!SkillWidget)
		{
			SkillWidget = CreateWidget<ULA_SkillWidget>(GetOwningPlayerController(), SkillWidgetClass);
		}
		if (SkillWidget)
		{
			if (SkillWidget->IsInViewport())
			{
				SkillWidget->RemoveFromParent();
				return;
			}
			SkillWidget->AddToViewport();
			
			// 1. 현재 뷰포트(화면) 사이즈 가져오기
			FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
			
			// 현재 뷰포트 스케일(DPI) 가져오기
			float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
			
			// 위젯의 크기 가져오기
			FVector2D WidgetSize = SkillWidget->GetDesiredSize();
			
			// 중앙 좌표 계산 (DPI 스케일 보정 필수)
			// (화면 크기 / 스케일 / 2) - (위젯 크기 / 2)
			FVector2D CenterPos = (ViewportSize / ViewportScale * 0.5f) - (WidgetSize * 0.5f);
			
			SkillWidget->SetPositionInViewport(CenterPos);
		}
	}
}


