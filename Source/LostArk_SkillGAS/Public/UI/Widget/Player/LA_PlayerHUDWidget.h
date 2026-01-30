#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LA_PlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HPBar;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* MPBar;
	
	// 데이터를 업데이트하는 함수
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	void UpdateMana(float CurrentMana, float MaxMana);
};
