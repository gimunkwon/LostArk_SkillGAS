#include "UI/Widget/Player/LA_PlayerHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ULA_PlayerHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HPBar && MaxHealth > 0.f)
	{
		HPBar->SetPercent(CurrentHealth / MaxHealth);
		if (HPText)
		{
			HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"),CurrentHealth,MaxHealth)));
		}
	}
}

void ULA_PlayerHUDWidget::UpdateMana(float CurrentMana, float MaxMana)
{
	if (MPBar && MaxMana > 0.f)
	{
		MPBar->SetPercent(CurrentMana / MaxMana);
		if (MPText)
		{
			MPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"),CurrentMana,MaxMana)));
		}
	}
}
