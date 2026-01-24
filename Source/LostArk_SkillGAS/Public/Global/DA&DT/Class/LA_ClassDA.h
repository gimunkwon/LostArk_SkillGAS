#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "LA_ClassDA.generated.h"

class ULA_ClassDA;

USTRUCT(BlueprintType)
struct FClassDT : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category="Name")
	FGameplayTag ClassName;
	UPROPERTY(EditAnywhere,Category="Stat")
	float MaxHP;
	UPROPERTY(EditAnywhere,Category="Stat")
	float MaxMP;
	UPROPERTY(EditAnywhere,Category="Stat")
	float AttackPower;
	UPROPERTY(EditAnywhere,Category="DataAsset")
	TSoftObjectPtr<ULA_ClassDA> ClassAsset;
};




UCLASS(BlueprintType)
class LOSTARK_SKILLGAS_API ULA_ClassDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("SubClassData",GetFName());
	}
	UPROPERTY(EditAnywhere,Category="DataMap | Animations")
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> SkillAnimMontageMap;
};
