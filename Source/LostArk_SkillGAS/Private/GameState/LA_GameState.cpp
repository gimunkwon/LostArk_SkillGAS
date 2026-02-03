#include "GameState/LA_GameState.h"

#include "PlayerState/LA_PlayerState.h"

void ALA_GameState::RegisterPartyMember(FGuid PartyID, ALA_PlayerState* NewMember, bool bIsLeader)
{
	if (!NewMember) return;
	
	// 기존 파티가 있는지 확인, 없으면 새로 생성
	FLA_PartyInfo& PartyInfo = PartyMap.FindOrAdd(PartyID);
	
	// 새로 생성된 경우
	if (PartyInfo.PartyID == FGuid())
	{
		PartyInfo.Members.Add(NewMember);
	}
	
	// 3. 파티장 설정
	if (bIsLeader)
	{
		PartyInfo.Leader = NewMember;
	}
	
	UE_LOG(LogTemp,Warning,TEXT("GameState: Player %s Registered to Party %s")
		,*NewMember->GetPlayerName(), *PartyID.ToString());
}

FLA_PartyInfo* ALA_GameState::GetPartyInfo(FGuid PartyID)
{
	return PartyMap.Find(PartyID);
}
