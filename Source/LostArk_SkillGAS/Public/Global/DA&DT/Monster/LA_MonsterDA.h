#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "LA_MonsterDA.generated.h"

class ULA_MonsterDA;

USTRUCT(BlueprintType)
struct FMonsterDT : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category="Name")
	FGameplayTag MonsterName;
	UPROPERTY(EditAnywhere,Category="Stat")
	float MaxHP;
	UPROPERTY(EditAnywhere,Category="Stat")
	float AttackPower;
	UPROPERTY(EditAnywhere,Category="DataAsset")
	TSoftObjectPtr<ULA_MonsterDA> MonsterAsset;
};



UCLASS()
class LOSTARK_SKILLGAS_API ULA_MonsterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("SubMonsterData",GetFName());
	}
	UPROPERTY(EditAnywhere,Category="DataMap | Animations")
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> SkillAnimMontageMap;
};
