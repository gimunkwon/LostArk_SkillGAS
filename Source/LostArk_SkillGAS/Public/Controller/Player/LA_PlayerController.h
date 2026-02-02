#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LA_PlayerController.generated.h"

class ALA_BaseCharacter;
class UInputMappingContext;
class UInputAction;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALA_PlayerController();
#pragma region Party
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_SendPartyInvite(ALA_BaseCharacter* Target);
	// 상대방에게 팝업을 띄우라고 명령(Server -> Target Client)
	UFUNCTION(Client, Reliable)
	void Client_SendPartyInvite(ALA_BaseCharacter* Inviter);
	// 파티 거절 수락 팝업위젯 서버 RPC함수
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ReplyToInvite(ALA_BaseCharacter* Inviter, bool bAccepted);
#pragma endregion

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// Default MappingContext
	UPROPERTY(EditAnywhere,Category="Input|MappingContext")
	UInputMappingContext* DefaultMappingContext;
	// InputAction
	UPROPERTY(EditAnywhere,Category="Input|InputAction")
	UInputAction* IA_ClickToMove;
	// InputAction Binding Function
	void OnInputStarted();
	
	
};
