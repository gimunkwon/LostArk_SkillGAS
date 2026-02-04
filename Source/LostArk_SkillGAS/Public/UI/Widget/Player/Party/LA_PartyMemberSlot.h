#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Base/AttributeSet/LA_BaseAttributeSet.h"
#include "LA_PartyMemberSlot.generated.h"

class UTextBlock;
class UProgressBar;
class ALA_PlayerState;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_PartyMemberSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 데이터를 주입하고 초기화하는 핵심 함수
	void SetupSlot(ALA_PlayerState* InPs);
	
protected:
	// HP 변경 시 호출될 콜백
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;
	
	// 관찰 대상 (약참조로 안전하게 관리)
	TWeakObjectPtr<ALA_PlayerState> TargetPS;
};
