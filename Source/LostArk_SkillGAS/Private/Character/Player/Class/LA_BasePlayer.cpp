#include "Character/Player/Class/LA_BasePlayer.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerState/LA_PlayerState.h"

ALA_BasePlayer::ALA_BasePlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 600.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f,0.f,0.f));
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	TopDownCamera->SetupAttachment(SpringArmComponent);
	
}

void ALA_BasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// 서버에서 호출됨(빙의 시점)
void ALA_BasePlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// 서버 측 GAS 초기화
	InitAbilityActorInfo();
}
// 클라이언트에서 호출됨 (PlayerState 복제 시점)
void ALA_BasePlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// 클라이언트 측 GAS 초기화
	InitAbilityActorInfo();
}

void ALA_BasePlayer::InitAbilityActorInfo()
{
	ALA_PlayerState* PS = GetPlayerState<ALA_PlayerState>();
	if (PS)
	{
		// [결속] PlayerState의 ASC를 가져와서 나(this)를 아바타로 설정
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PS, this);
		// 부모 클래스가 가진 포인터도 업데이트(편의성)
		AbilitySystemComponent = ASC;
		// 데이터 주입 (서버에서만 주입하면 클라이언트로 복제됨)
		// 하지만 클라이언트에서도 초기값이 필요하므로 안전하게 호출
		
		FGameplayTag ClassTag = FGameplayTag::RequestGameplayTag(FName("Class.Warrior.Berserker"));
		PS->InitializeAttributesFromDataTable(ClassTag);
		
	}
}






