#include "UI/Widget/Player/Party/LA_PartyMemberSlot.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerState/LA_PlayerState.h"

void ULA_PartyMemberSlot::SetupSlot(ALA_PlayerState* InPs)
{
	if (!InPs) return;
	TargetPS = InPs;
	
	// 1. 초기 텍스트 설정
	PlayerNameText->SetText(FText::FromString(InPs->GetPlayerName()));
	
	// 2. GAS Attribute 변경 감지 바인딩
	if (UAbilitySystemComponent* ASC = InPs->GetAbilitySystemComponent())
	{
		// 체력 속성이 변할 때마다 OnHealthChanged를 실행하도록 바인딩
		ASC->GetGameplayAttributeValueChangeDelegate(ULA_BaseAttributeSet::GetHealthAttribute()).AddUObject(this, &ULA_PartyMemberSlot::OnHealthChanged);
		
		// 3. 현재 값으로 초기 HP 설정
		float CurrentHP = InPs->GetBaseAttributeSet()->GetHealth();
		float MaxHP = InPs->GetBaseAttributeSet()->GetMaxHealth();
		HealthBar->SetPercent(MaxHP > 0.f ? CurrentHP / MaxHP : 0.f);
	}
}

void ULA_PartyMemberSlot::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (TargetPS.IsValid())
	{
		float MaxHP = TargetPS->GetBaseAttributeSet()->GetMaxHealth();
		HealthBar->SetPercent(MaxHP > 0.f ? Data.NewValue / MaxHP : 0.f);
	}
}
