#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LostArk_SkillGAS/LostArk_SkillGAS.h"
#include "LA_BaseAttributeSet.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ULA_BaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// HP
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULA_BaseAttributeSet, Health);
	// 공격력
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(ULA_BaseAttributeSet, AttackPower);
};
