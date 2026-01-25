#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "LA_BaseMonsterDA.generated.h"

class ULA_BaseMonsterDA;

USTRUCT(BlueprintType)
struct FBaseMonsterDT : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Class")
	FGameplayTag BaseMonsterTag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Name")
	FText BaseMonsterDisplayName;
	UPROPERTY(EditAnywhere,Category="DataAsset")
	TSoftObjectPtr<ULA_BaseMonsterDA> BaseMonsterDA;
};




UCLASS()
class LOSTARK_SKILLGAS_API ULA_BaseMonsterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	// 에셋 매니저가 이 에셋을 식별하기 위한 신분증 생성 함수
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("BaseMonsterData",GetFName());
	}
	UPROPERTY(EditAnywhere,Category="DataTable")
	TMap<FGameplayTag, FDataTableRowHandle> BaseMonsterData;
};
