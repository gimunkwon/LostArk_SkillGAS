#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LA_AssetManager.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ULA_AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	ULA_AssetManager();
	virtual void StartInitialLoading() override;
};
