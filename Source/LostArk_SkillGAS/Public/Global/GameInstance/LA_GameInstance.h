#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LA_GameInstance.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ULA_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// 게임 인스턴스가 초기화 될 때 호출(서버/클라이언트 공통)
	virtual void Init() override;
};
