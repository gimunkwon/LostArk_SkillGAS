#include "Character/Player/Class/LA_BasePlayer.h"

#include "AbilitySystemComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerState/LA_PlayerState.h"

ALA_BasePlayer::ALA_BasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
#pragma region Camera,SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 600.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f,0.f,0.f));
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	TopDownCamera->SetupAttachment(SpringArmComponent);
	TopDownCamera->bUsePawnControlRotation = false;
#pragma endregion
	
#pragma region Movement,Rotation
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	bReplicates = true; // 액터 복제 활성화
	GetCharacterMovement()->SetIsReplicated(true);
	AActor::SetReplicateMovement(true);
	bIsMovingToPath = false;
#pragma endregion
	
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

void ALA_BasePlayer::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ALA_BasePlayer, PathPoints);
	DOREPLIFETIME(ALA_BasePlayer, bIsMovingToPath);
}

void ALA_BasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALA_BasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsMovingToPath && IsLocallyControlled())
	{
		ProcessPathMovement();
	}
	
	if (GEngine && IsLocallyControlled())
	{
		FString IsMovingToPath = bIsMovingToPath ? TEXT("true") : TEXT("false");
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, IsMovingToPath);
	}
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
		
		FGameplayTag ClassTag = PS->GetSelectedClassTag();
		
		if (ClassTag.IsValid())
		{
			PS->InitializeAttributesFromDataTable(ClassTag);
		}
		
	}
}

// Client
void ALA_BasePlayer::RequestToMove(FVector TargetLocation)
{
	if (IsLocallyControlled())
	{
		Server_MoveToLocaiton(TargetLocation);
	}
}

// RPC
void ALA_BasePlayer::Server_MoveToLocaiton_Implementation(FVector TargetLocation)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return;
	
	// 서버의 NavMesh를 사용하여 동기적으로 경로 탐색
	UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), TargetLocation);
	
	if (NavPath && NavPath->IsValid())
	{
		PathPoints = NavPath->PathPoints;
		CurrentWayPointIndex = 1;
		bIsMovingToPath = true;
	}
}

// Client
void ALA_BasePlayer::ProcessPathMovement()
{
	if (CurrentWayPointIndex >= PathPoints.Num())
	{
		Server_StopMove();
		return;
	}
	
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = PathPoints[CurrentWayPointIndex];
	
	FVector Direction = TargetLocation - CurrentLocation;
	float DistanceToTarget = Direction.Size2D();
	
	// 높이 차이는 무시하고 방향 계산
	Direction.Z = 0.f;
	Direction.Normalize();
	
	AddMovementInput(Direction, 1.f);
	
	if (DistanceToTarget < 20.f)
	{
		CurrentWayPointIndex++;
	}
	
}

void ALA_BasePlayer::Server_StopMove_Implementation()
{
	
	bIsMovingToPath = false;
	CurrentWayPointIndex = 0;
	PathPoints.Empty();
	
	
}


