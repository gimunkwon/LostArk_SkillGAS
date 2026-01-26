#include "PlayerState/LA_PlayerState.h"

#include "AbilitySystemComponent.h"
#include "Character/Base/AttributeSet/LA_BaseAttributeSet.h"
#include "Character/Player/Attribute/LA_ClassAttributeset.h"
#include "Character/Player/Class/LA_BasePlayer.h"
#include "Global/DA&DT/Base/LA_BaseClassDA.h"
#include "Global/DA&DT/Class/LA_ClassDA.h"
#include "Net/UnrealNetwork.h"


ALA_PlayerState::ALA_PlayerState()
{
	// 1. ASC 생성 및 멀티플레이 설정
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	// Mixed 모드 : 플레이어 캐릭터에 최적화된 복제 방식
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	// AttributeSet 조립
	BaseAttributeSet = CreateDefaultSubobject<ULA_BaseAttributeSet>(FName("BaseAttributeSet"));
	ClassAttributeSet = CreateDefaultSubobject<ULA_ClassAttributeset>(FName("AttributeSet"));
	// 서버 업데이트 빈도
	// NetUpdateFrequency = 100.f;
	
}

void ALA_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//SelectedClassTag가 네트워크를 타고 복제되도록 등록
	DOREPLIFETIME(ALA_PlayerState, SelectedClassTag);
}

UAbilitySystemComponent* ALA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALA_PlayerState::InitializeAttributesFromDataTable(FGameplayTag ClassTag)
{
	if (!BaseClassDataTable || !ClassTag.IsValid()) return;
	// UE_LOG(LogTemp,Warning,TEXT("InitializeAttributesFromDataTable %s"),*ClassTag.ToString());
	// GameplayTag를 문자열로 변환하여 Row 찾기 (예: "Class.Warrior.Berserker")
	
	// 1. 태그분석
	FGameplayTag BaseClassTag = ClassTag.RequestDirectParent();
	// 행 이름 설정
	FName SubClassRowName = FName(*ClassTag.GetTagLeafName().ToString());
	// UE_LOG(LogTemp,Warning,TEXT("SubClassRowName : %s"),*SubClassRowName.ToString());
	FName BaseClassRowName = FName(*BaseClassTag.GetTagLeafName().ToString());
	// UE_LOG(LogTemp,Warning,TEXT("BaseClassRowName : %s"),*BaseClassRowName.ToString());
	
	// BaseClassDataTable에서 BaseClassDA 찾기
	FBaseClassDT* BaseRow = BaseClassDataTable->FindRow<FBaseClassDT>(BaseClassRowName,TEXT("BaseDAFetch"));
	if (BaseRow)
	{
		// 소프트 포인터 로드
		if (BaseRow->BaseClassDA.IsPending()) BaseRow->BaseClassDA.LoadSynchronous();
		
		ULA_BaseClassDA* BaseDA = BaseRow->BaseClassDA.Get();
		if (BaseDA)
		{
			// [메시 적용] DA가 들고 있는 메시를 캐릭터에게 전달
			if (ALA_BasePlayer* BasePlayer = Cast<ALA_BasePlayer>(GetPawn()))
			{
				BasePlayer->GetMesh()->SetSkeletalMesh(BaseDA->BaseClassMesh);
			}
			
			// BaseDA 내부의 Map에서 세부 전직 DT핸들 찾기
			if (BaseDA->BaseClassData.Contains(ClassTag))
			{
				FDataTableRowHandle StatRowHandle = BaseDA->BaseClassData[ClassTag];
				FClassDT* ClassRow = StatRowHandle.GetRow<FClassDT>(TEXT("StatInit"));
				
				if (ClassRow)
				{
					// [스탯 주입]
					if (BaseAttributeSet)
					{
						BaseAttributeSet->InitHealth(ClassRow->MaxHP);
						BaseAttributeSet->InitMaxHealth(ClassRow->MaxHP);
						BaseAttributeSet->InitAttackPower(ClassRow->AttackPower);
					}
					if (ClassAttributeSet)
					{
						ClassAttributeSet->InitMana(ClassRow->MaxMP);
						ClassAttributeSet->InitMaxMP(ClassRow->MaxMP);
					}
				}
			}
		}
		
	}
}


