#include "Controller/Player/LA_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/Player/Class/LA_BasePlayer.h"

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
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility,false, Hit))
	{
		if (ALA_BasePlayer* MyPawn = Cast<ALA_BasePlayer>(GetPawn()))
		{
			// 플레이어 이동 RPC 함수
			Hit.Location.Z = 0.f;
			UE_LOG(LogTemp,Warning,TEXT("OnInputStarted"));
			MyPawn->RequestToMove(Hit.Location);
		}
	}
}
