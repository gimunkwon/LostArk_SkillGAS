#pragma once

#include "CoreMinimal.h"
#include "LA_PartyManager.generated.h"

class ALA_PlayerState;

USTRUCT(BlueprintType)
struct FLA_PartyInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FGuid PartyID;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ALA_PlayerState>> Members;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ALA_PlayerState> Leader;
	
	FLA_PartyInfo() : PartyID(FGuid()), Leader(nullptr){}
	
};
