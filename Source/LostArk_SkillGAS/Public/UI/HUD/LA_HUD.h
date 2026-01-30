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
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	
};
