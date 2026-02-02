#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
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
protected:
	// 멀티플레이어 변수 복제를 위한 함수 선언
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma region GASComponent
	// GAS 핵심 컴포넌트
	UPROPERTY(VisibleAnywhere,Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
#pragma endregion
#pragma region AttributeSetData
	// 모든 캐릭터 공통 스탯
	UPROPERTY()
	TObjectPtr<ULA_BaseAttributeSet> BaseAttributeSet;
	// 플레이어 전용 스탯
	UPROPERTY()
	TObjectPtr<ULA_ClassAttributeset> ClassAttributeSet;
#pragma endregion
#pragma region DataTable
	// 데이터 테이블 설정
	UPROPERTY(EditDefaultsOnly, Category="Stat|Data")
	TObjectPtr<UDataTable> BaseClassDataTable;
#pragma endregion
#pragma region GamePlayTag
	// 클래스 태그
	UPROPERTY(Replicated, VisibleAnywhere, Category="GAS|Data")
	FGameplayTag SelectedClassTag;
#pragma endregion
#pragma region PartySystem
	// 파티 ID
	UPROPERTY(ReplicatedUsing= OnRep_PartyID, BlueprintReadOnly, Category="Party")
	FGuid PartyID;
	UFUNCTION()
	void OnRep_PartyID();
#pragma endregion
public:
#pragma region GASComponent
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion
#pragma region AttributeSetData
	// AttributeSet Getter들
	ULA_BaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}
	ULA_ClassAttributeset* GetClassAttributeSet() const {return ClassAttributeSet;}
#pragma endregion
	// 데이터 테이블 등을 이용해 스탯을 초기화하는 함수
	void InitializeAttributesFromDataTable(FGameplayTag ClassTag);
#pragma region GameplayTag
	// 클래스 태그 세터함수
	UFUNCTION()
	void SetSelectedClassTag(FGameplayTag InTag) {SelectedClassTag = InTag;}
	// 클래스 태그 게터함수
	FORCEINLINE FGameplayTag GetSelectedClassTag() const {return SelectedClassTag;}
#pragma endregion
#pragma region PartySystem
	// 플레이어가 파티 상태인지 확인하는 함수
	bool IsInParty() const;
	// 서버에 등록된 파티데이터 Getter/Setter 함수
	void SetPartID(const FGuid& NewID) {PartyID = NewID;}
	FGuid GetPartID() const {return PartyID;}
#pragma endregion
};
