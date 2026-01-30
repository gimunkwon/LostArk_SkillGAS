#include "UI/Widget/Player/LA_PlayerHUDWidget.h"

#include "Components/ProgressBar.h"

void ULA_PlayerHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HPBar && MaxHealth > 0.f)
	{
		HPBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void ULA_PlayerHUDWidget::UpdateMana(float CurrentMana, float MaxMana)
{
	if (MPBar && MaxMana > 0.f)
	{
		MPBar->SetPercent(CurrentMana / MaxMana);
	}
}
