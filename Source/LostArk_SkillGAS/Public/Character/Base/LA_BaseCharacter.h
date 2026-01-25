#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "LA_BaseCharacter.generated.h"

class UWidgetComponent;
class UAttributeSet;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALA_BaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	virtual void BeginPlay() override;
#pragma region ASC
	// GAS 핵심 컴포넌트
	UPROPERTY(VisibleAnywhere,Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
#pragma endregion
	
	// 공통 외형 및 정보
	UPROPERTY(EditAnywhere,Category="CharacterInfo | Name")
	FText CharacterName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> CommonWidgetComponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="UI")
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	
	// 초기화 로직
	virtual void InitAbilityActorInfo(); // ASC와 액터 연결
	virtual void InitializeAttributes(); // 기본 스탯 주입
	virtual void AddCharacterAbilities(); // 기본 스킬 부여
	
	// 사망 로직
	virtual void Die();
};
