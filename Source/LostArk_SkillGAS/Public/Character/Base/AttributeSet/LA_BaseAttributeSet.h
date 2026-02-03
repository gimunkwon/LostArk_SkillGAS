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
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health ,Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULA_BaseAttributeSet, Health);
	// MAXHP
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth ,Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULA_BaseAttributeSet, MaxHealth);
	// 공격력
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_AttackPower,Category="Attributes")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(ULA_BaseAttributeSet, AttackPower);
	
	// OnRep 함수 선언 (클라이언트 알림용)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	
	// 네트워크 복제 등록
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
