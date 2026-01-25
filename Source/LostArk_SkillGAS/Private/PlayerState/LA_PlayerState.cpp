#include "PlayerState/LA_PlayerState.h"

ALA_PlayerState::ALA_PlayerState()
{
}

UAbilitySystemComponent* ALA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
