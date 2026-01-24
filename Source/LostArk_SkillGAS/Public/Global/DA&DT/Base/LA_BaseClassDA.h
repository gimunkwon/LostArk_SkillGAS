#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "LA_BaseClassDA.generated.h"

class ULA_BaseClassDA;

USTRUCT(BlueprintType)
struct FBaseClassDT : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Class")
	FGameplayTag BaseClassTag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Name")
	FText BaseClassDisplayName;
	UPROPERTY(EditAnywhere,Category="DataAsset")
	TSoftObjectPtr<ULA_BaseClassDA> BaseClassDA;
};



UCLASS(BlueprintType)
class LOSTARK_SKILLGAS_API ULA_BaseClassDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	// 에셋 매니저가 이 에셋을 식별하기 위한 신분증 생성 함수
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("BaseClassData",GetFName());
	}
	UPROPERTY(EditAnywhere,Category="DataTable")
	TMap<FGameplayTag, FDataTableRowHandle> BaseClassData;
};
