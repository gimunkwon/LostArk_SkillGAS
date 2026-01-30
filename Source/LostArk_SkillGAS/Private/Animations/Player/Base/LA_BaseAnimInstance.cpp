#include "Animations/Player/Base/LA_BaseAnimInstance.h"
#include "Character/Base/LA_BaseCharacter.h"

void ULA_BaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwnerCharacter = Cast<ALA_BaseCharacter>(TryGetPawnOwner());
	
	if (OwnerCharacter)
	{
		OwnerMovement = OwnerCharacter->GetCharacterMovement();
	}
}

void ULA_BaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		GroundSpeed = OwnerCharacter->GetVelocity().Size2D();
	}
}
