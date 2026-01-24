#include "Global/GamePlayTag/LA_AssetManager.h"
#include "GameplayTags.h"
#include "Global/GamePlayTag/LA_GamePlayTags.h"


ULA_AssetManager::ULA_AssetManager()
{
	UE_LOG(LogTemp, Error, TEXT("==== LA_AssetManager: Constructor Called! ===="));
}

void ULA_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UE_LOG(LogTemp,Warning,TEXT("======LA_AssetManager::START INITIAL LOADING========"));
	
	// 엔진이 초기 로딩을 시작할때 태그들 등록
	FLA_GamePlayTags::InitializeNativeTags();
}
