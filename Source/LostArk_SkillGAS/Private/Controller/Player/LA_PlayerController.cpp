#include "Controller/Player/LA_PlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Character/Base/AttributeSet/LA_BaseAttributeSet.h"
#include "Character/Player/Class/LA_BasePlayer.h"
#include "GameState/LA_GameState.h"
#include "LostArk_SkillGAS/LostArk_SkillGAS.h"
#include "PlayerState/LA_PlayerState.h"
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

#pragma region InputMapping,InputAction
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
		
		// if (HitActor)
		// {
		// 	UE_LOG(LogTemp,Warning,TEXT("Hit Actor: %s, Channel: Visibility"), *HitActor->GetName());
		// }
		
		// Shift + 우클릭인 경우 : 컨텍스트 메뉴 로직
		if (bIsShiftDown && HitActor)
		{
			ALA_BaseCharacter* TargetPlayer = Cast<ALA_BaseCharacter>(Hit.GetActor());
			
			if (TargetPlayer && TargetPlayer != GetPawn())
			{
				UE_LOG(LogTemp,Warning,TEXT("ShowContextMenu"));
				if (PlayerHUD) PlayerHUD->ShowContextMenu(TargetPlayer);
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
#pragma endregion 

#pragma region PartySystem
// 파티요청 ServerRPC
void ALA_PlayerController::Server_SendPartyInvite_Implementation(ALA_BaseCharacter* Target)
{
	if (!Target) return;
	
	ALA_PlayerState* TargetPS = Target->GetPlayerState<ALA_PlayerState>();
	if (!TargetPS) return;
	
	// 상대방이 이미 파티 중인지 확인
	if (TargetPS->IsInParty())
	{
		// 초대자(나)에게 알림 전송
		UE_LOG(LogTemp,Warning,TEXT("상대방이 이미 파티에 속해있습니다."));
		return;
	}
	
	// 초대 받을 대상의 Controller 찾기
	ALA_PlayerController* TargetPC = Cast<ALA_PlayerController>(Target->GetController());
	
	if (TargetPC)
	{
		TargetPC->Client_SendPartyInvite(Cast<ALA_BaseCharacter>(GetPawn()));
	}
}
// 유효성 검사
bool ALA_PlayerController::Server_SendPartyInvite_Validate(ALA_BaseCharacter* Target)
{
	return true;
}
// 파티요청 ClientRPC
void ALA_PlayerController::Client_SendPartyInvite_Implementation(ALA_BaseCharacter* Inviter)
{
	if (ALA_HUD* PlayerHUD = GetHUD<ALA_HUD>())
	{
		PlayerHUD->ShowInvitePopUp(Inviter);
	}
}
// 파티수락후 파티생성 ServerRPC
void ALA_PlayerController::Server_ReplyToInvite_Implementation(ALA_BaseCharacter* Inviter, bool bAccepted)
{
	if (!Inviter) return;
	// 초대자(Inviter)의 PlayerState와 ASC가져오기
	ALA_PlayerState* InviterPS = Inviter->GetPlayerState<ALA_PlayerState>();
	// 수락자(본인)의 PlayerState와 ASC 가져오기
	ALA_PlayerState* MyPS = GetPlayerState<ALA_PlayerState>();
	if (bAccepted)
	{
		if (InviterPS && MyPS)
		{
			FGuid TargetPartyID;
			
			// 초대자가 이미 파티장인가(이미 파티가 있는 경우)
			if (InviterPS->GetPartyID().IsValid())
			{
				TargetPartyID = InviterPS->GetPartyID();
			}
			else
			{
				// 새로운 파티 생성 (새로운 GUID 발급)
				TargetPartyID = FGuid::NewGuid();
				InviterPS->SetPartID(TargetPartyID);
				
				
				// 초대자에게 파티장 태그 부여
				if (UAbilitySystemComponent* InviterASC = InviterPS->GetAbilitySystemComponent())
				{
					InviterASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Party.Leader")));
				}
			}
			// 수락자(나)에게 동일한 PartyID 설정 및 멤버 태그 부여
			MyPS->SetPartID(TargetPartyID);
			
			if (UAbilitySystemComponent* MyASC = MyPS->GetAbilitySystemComponent())
			{
				MyASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Party.Member")));
			}
			
			if (ALA_GameState* GS = GetWorld()->GetGameState<ALA_GameState>())
			{
				// 초대자 등록 (파티장)
				GS->RegisterPartyMember(TargetPartyID, InviterPS, true);
				// 나(수락자) 등록(멤버)
				GS->RegisterPartyMember(TargetPartyID, MyPS, false);
			}
			
			UE_LOG(LogTemp,Warning,TEXT("파티 결성 완료 ID: %s"), *TargetPartyID.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Server : %s declined invite from %s."), *GetName(), *Inviter->GetName());
	}
}
// 파티수락후 파티생성 유효성 검사
bool ALA_PlayerController::Server_ReplyToInvite_Validate(ALA_BaseCharacter* Inviter, bool bAccepted)
{
	return true;
}
#pragma endregion

#pragma region CheatFunc
void ALA_PlayerController::Cheat_SetHP(float NewHP)
{
	// 명령어 호출 시 서버로 Attribute 변경 요청
	Server_ModifyAttribute(ULA_BaseAttributeSet::GetHealthAttribute(), NewHP);
}

void ALA_PlayerController::Cheat_Damage(float Amount)
{
	if (ALA_PlayerState* PS = GetPlayerState<ALA_PlayerState>())
	{
		float CurrentHP = PS->GetBaseAttributeSet()->GetHealth();
		Server_ModifyAttribute(ULA_BaseAttributeSet::GetHealthAttribute(), CurrentHP - Amount);
	}
}

void ALA_PlayerController::Server_ModifyAttribute_Implementation(FGameplayAttribute Attribute, float NewValue)
{
	// 서버 권한으로 ASC의 Attribute를 직접 수정
	if (ALA_PlayerState* PS = GetPlayerState<ALA_PlayerState>())
	{
		if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			// BaseValue를 직접 수정하여 클라이언트에 복제되도록 함
			ASC->SetNumericAttributeBase(Attribute, NewValue);
			
			UE_LOG(LogTemp,Warning,TEXT("Server: %s's %s Changed to %f"),
				*GetName(), *Attribute.GetName(), NewValue);
		}
	}
}
#pragma endregion