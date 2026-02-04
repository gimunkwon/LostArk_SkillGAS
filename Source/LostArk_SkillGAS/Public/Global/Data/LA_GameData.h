#pragma once

#include "CoreMinimal.h"
#include "LA_GameData.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInfoBase // 공통 부모
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Montage;
};

// 스킬 전용 구조체
USTRUCT(BlueprintType)
struct FSkillAttributeInfo : public FAbilityInfoBase
{
	GENERATED_BODY()
};


// 대쉬 전용 구조체
USTRUCT(BlueprintType)
struct FDashAttributeInfo : public FAbilityInfoBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float DashDistance = 500.f;
};
