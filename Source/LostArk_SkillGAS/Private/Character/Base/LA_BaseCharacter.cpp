#include "Character/Base/LA_BaseCharacter.h"
#include "AbilitySystemComponent.h"


ALA_BaseCharacter::ALA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ALA_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

UAbilitySystemComponent* ALA_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALA_BaseCharacter::InitAbilityActorInfo()
{
	// 오버라이드 예정
}

void ALA_BaseCharacter::InitializeAttributes()
{
	// 데이터 에셋으로부터 값을 읽어와서 GamePlayEffect로 스탯을 꽂아넣는 로직
}

void ALA_BaseCharacter::AddCharacterAbilities()
{
	// 기본 공격, 스킬 등을 ASC에 등록하는 로직
}

void ALA_BaseCharacter::Die()
{
	// 사망 애니메이션 재생, 콜라이더 끄기
}


