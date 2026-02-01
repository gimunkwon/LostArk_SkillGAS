#include "Controller/Player/LA_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Character/Player/Class/LA_BasePlayer.h"
#include "LostArk_SkillGAS/LostArk_SkillGAS.h"
#include "UI/HUD/LA_HUD.h"
#include "Windows/WindowsApplication.h"

ALA_PlayerController::ALA_PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bReplicates = true;
}

void ALA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ALA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EInputComp = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EInputComp->BindAction(IA_ClickToMove,ETriggerEvent::Started,this,&ALA_PlayerController::OnInputStarted);
		EInputComp->BindAction(IA_ClickToMove, ETriggerEvent::Triggered, this, &ALA_PlayerController::OnInputStarted);
	}
}

void ALA_PlayerController::OnInputStarted()
{
	// 1. Shift 키가 눌려있는지 확인
	const bool bIsShiftDown = IsInputKeyDown(EKeys::LeftShift) || IsInputKeyDown(EKeys::RightShift);
	ALA_HUD* PlayerHUD = GetHUD<ALA_HUD>();
	FHitResult Hit;
	
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		AActor* HitActor = Hit.GetActor();
		
		if (HitActor)
		{
			UE_LOG(LogTemp,Warning,TEXT("Hit Actor: %s, Channel: Visibility"), *HitActor->GetName());
		}
		
		// Shift + 우클릭인 경우 : 컨텍스트 메뉴 로직
		if (bIsShiftDown && HitActor)
		{
			ALA_BaseCharacter* TargetPlayer = Cast<ALA_BaseCharacter>(Hit.GetActor());
			
			if (TargetPlayer && TargetPlayer != GetPawn())
			{
				UE_LOG(LogTemp,Warning,TEXT("ShowContextMenu"));
				if (PlayerHUD) PlayerHUD->ShowContextMenu();
				return;
			}
		}
		
		// 이동 로직
		if (ALA_BasePlayer* MyPawn = Cast<ALA_BasePlayer>(GetPawn()))
		{
			if (PlayerHUD) PlayerHUD->HideContextMenu();
			// 플레이어 이동 RPC 함수
			Hit.Location.Z = 0.f;
			MyPawn->RequestToMove(Hit.Location);
		}
	}
	
}

