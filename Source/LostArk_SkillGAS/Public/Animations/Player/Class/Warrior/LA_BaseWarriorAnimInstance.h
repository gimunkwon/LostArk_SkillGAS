#pragma once

#include "CoreMinimal.h"
#include "Animations/Player/Base/LA_BaseAnimInstance.h"
#include "LA_BaseWarriorAnimInstance.generated.h"


UCLASS()
class LOSTARK_SKILLGAS_API ULA_BaseWarriorAnimInstance : public ULA_BaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
