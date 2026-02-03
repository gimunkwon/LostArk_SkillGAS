#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Global/Party/LA_PartyManager.h"
#include "LA_GameState.generated.h"


UCLASS()
class LOSTARK_SKILLGAS_API ALA_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// 서버에서 관리하는 전체 파티 맵
	TMap<FGuid, FLA_PartyInfo> PartyMap;
	
	// 파티 생성 또는 멤버 추가 함수
	void RegisterPartyMember(FGuid PartyID, ALA_PlayerState* NewMember, bool bIsLeader);
	// 파티 정보 조회
	FLA_PartyInfo* GetPartyInfo(FGuid PartyID);
};
