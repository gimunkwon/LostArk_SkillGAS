#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LA_BaseAnimInstance.generated.h"


class UCharacterMovementComponent;
class ALA_BaseCharacter;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_BaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	TObjectPtr<ALA_BaseCharacter> OwnerCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement|Component")
	TObjectPtr<UCharacterMovementComponent> OwnerMovement;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement|Speed")
	float GroundSpeed;
};
