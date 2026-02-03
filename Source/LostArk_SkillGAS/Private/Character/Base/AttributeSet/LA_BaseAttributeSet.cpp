#include "Character/Base/AttributeSet/LA_BaseAttributeSet.h"

#include "Net/UnrealNetwork.h"

// 네트워크 복제 규칙 정의
void ULA_BaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// 속성들이 네트워크를 통해 복제되도록 등록
	DOREPLIFETIME_CONDITION_NOTIFY(ULA_BaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULA_BaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULA_BaseAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
}

void ULA_BaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	// 이 매크로가 클라이언트의 ASC 델리게이트를 트리거
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULA_BaseAttributeSet, Health, OldHealth);
}

void ULA_BaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULA_BaseAttributeSet, MaxHealth, OldMaxHealth);
}

void ULA_BaseAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULA_BaseAttributeSet, AttackPower, OldAttackPower);
}


