#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LA_HUD.generated.h"

class ULA_PlayerHUDWidget;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UPROPERTY()
	TObjectPtr<ULA_PlayerHUDWidget> PlayerHUDWidget;
	
	// 컨텍스트 메뉴를 띄우는 인터페이스
	void ShowContextMenu();
	// 메뉴 닫기
	void HideContextMenu();
protected:
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	// 컨택스트 메뉴 위젯클래스
	UPROPERTY(EditAnywhere, Category="UI|ContextMenu")
	TSubclassOf<UUserWidget> ContextMenuClass;
	
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> ContextMenuWidget;
};
