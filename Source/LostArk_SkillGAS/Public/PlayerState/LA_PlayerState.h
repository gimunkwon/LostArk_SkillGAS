#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "LA_PlayerState.generated.h"

struct FGameplayTag;
class UGameplayEffect;
class ULA_ClassAttributeset;
class ULA_BaseAttributeSet;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_PlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ALA_PlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// AttributeSet Getter들
	ULA_BaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}
	ULA_ClassAttributeset* GetClassAttributeSet() const {return ClassAttributeSet;}
	
	// 데이터 테이블 등을 이용해 스탯을 초기화하는 함수
	void InitializeAttributesFromDataTable(FGameplayTag ClassTag);
	
protected:
	// GAS 핵심 컴포넌트
	UPROPERTY(VisibleAnywhere,Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	// 모든 캐릭터 공통 스탯
	UPROPERTY()
	TObjectPtr<ULA_BaseAttributeSet> BaseAttributeSet;
	// 플레이어 전용 스탯
	UPROPERTY()
	TObjectPtr<ULA_ClassAttributeset> ClassAttributeSet;
	// 데이터 테이블 설정
	UPROPERTY(EditDefaultsOnly, Category="Stat|Data")
	TObjectPtr<UDataTable> BaseClassDataTable;
};
