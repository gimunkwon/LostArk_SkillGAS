#pragma once

#include "CoreMinimal.h"
#include "Character/Base/LA_BaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "LA_BasePlayer.generated.h"

class ULA_BaseClassDA;
class ULA_ClassAttributeset;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_BasePlayer : public ALA_BaseCharacter
{
	GENERATED_BODY()
public:
	ALA_BasePlayer();
	virtual void Tick(float DeltaTime) override;
	// GAS 초기화
	virtual void InitAbilityActorInfo() override;
	// 클라이언트에서 호출할 함수
	void RequestToMove(FVector TargetLocation);
#pragma region Movement
#pragma endregion
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma region Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera | SpringArm")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera | Camera")
	UCameraComponent* TopDownCamera;
#pragma endregion
#pragma region AttributeSet
	UPROPERTY()
	TObjectPtr<ULA_ClassAttributeset> ClassAttributeSet;
#pragma endregion
#pragma region Movement Value
	// 서버에서 실행될 경로 계산 RPC
	UFUNCTION(Server, Reliable)
	void Server_MoveToLocaiton(FVector TargetLocation);
	
	// 현재 따라가고 있는 경로 지점들
	UPROPERTY(Replicated)
	TArray<FVector> PathPoints;
	
	UPROPERTY(Replicated)
	int32 CurrentWayPointIndex = 1;
	
	UPROPERTY(Replicated)
	bool bIsMovingToPath;
	// 경로 이동 로직 처리
	UFUNCTION()
	void ProcessPathMovement();
	// 서버 이동 중지 함수
	UFUNCTION(Server,Reliable)
	void Server_StopMove();
#pragma endregion
	
};
