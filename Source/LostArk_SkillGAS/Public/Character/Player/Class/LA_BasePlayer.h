#pragma once

#include "CoreMinimal.h"
#include "Character/Base/LA_BaseCharacter.h"
#include "LA_BasePlayer.generated.h"

class ULA_ClassAttributeset;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_BasePlayer : public ALA_BaseCharacter
{
	GENERATED_BODY()
public:
	ALA_BasePlayer();
	// GAS 초기화
protected:
	virtual void BeginPlay() override;
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
	
private:
	void InitPlayerASC(); // 플레이어용 GAS 초기화 함수
};
