#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LA_PlayerHUDWidget.generated.h"

class UTextBlock;
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
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HPText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MPText;
	
	// 데이터를 업데이트하는 함수
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	void UpdateMana(float CurrentMana, float MaxMana);
};
