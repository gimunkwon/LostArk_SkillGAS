#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LostArk_SkillGAS/LostArk_SkillGAS.h"
#include "LA_ClassAttributeset.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ULA_ClassAttributeset : public UAttributeSet
{
	GENERATED_BODY()
public:
	// MP
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ULA_ClassAttributeset, Mana);
	// 아덴 게이지
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData IdentityGauge;
	ATTRIBUTE_ACCESSORS(ULA_ClassAttributeset, IdentityGauge);
};
