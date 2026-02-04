#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LA_HUD.generated.h"

class ALA_PlayerState;
class ULA_SkillWidget;
class ULA_PartyWidget;
class ULA_ContextMenuWidget;
class ALA_BaseCharacter;
class ULA_PlayerHUDWidget;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitOverlay(APlayerController* PC, ALA_PlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UPROPERTY()
	TObjectPtr<ULA_PlayerHUDWidget> PlayerHUDWidget;
#pragma region PartyWidgetFunc
	// 컨텍스트 메뉴를 띄우는 인터페이스
	void ShowContextMenu(ALA_BaseCharacter* TargetPlayer);
	// 메뉴 닫기
	void HideContextMenu();
	// 팝업메뉴
	void ShowInvitePopUp(ALA_BaseCharacter* Inviter);
	// 파티 위젯
	void ShowPartyWidget();
#pragma endregion
#pragma region SkillWidgetFunc
	void ToggleSkillWidget();
#pragma endregion 
protected:
#pragma region MainWidget
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
#pragma endregion
#pragma region PartyWidget
	// 컨택스트 메뉴 위젯클래스
	UPROPERTY(EditAnywhere, Category="UI|ContextMenu")
	TSubclassOf<UUserWidget> ContextMenuClass;
	// 초대 팝업 클래스
	UPROPERTY(EditAnywhere, Category="UI|PopupWidget")
	TSubclassOf<UUserWidget> InvitePopupClass;
	// 파티 위젯
	UPROPERTY(EditAnywhere, Category="UI|PartyWidget")
	TSubclassOf<UUserWidget> PartyWidgetClass;
	UPROPERTY()
	TObjectPtr<ULA_PartyWidget> PartyWidget;
#pragma endregion
#pragma region SkillWidget
	UPROPERTY(EditAnywhere,Category="UI|SkillWidget")
	TSubclassOf<UUserWidget> SkillWidgetClass;
	UPROPERTY()
	TObjectPtr<ULA_SkillWidget> SkillWidget;
#pragma endregion 
private:
	UPROPERTY()
	TObjectPtr<ULA_ContextMenuWidget> ContextMenuWidget;
	UFUNCTION()
	void HandleInviteRequest(ALA_BaseCharacter* Target);
};
