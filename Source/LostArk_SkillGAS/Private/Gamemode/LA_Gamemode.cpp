#include "Gamemode/LA_Gamemode.h"

#include "PlayerState/LA_PlayerState.h"

void ALA_Gamemode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	ALA_PlayerState* PS = NewPlayer->GetPlayerState<ALA_PlayerState>();
	if (PS)
	{
		// 접속 순서나 인덱스에 따라 다른 태그 부여
		int32 PlayerIndex = GetNumPlayers() - 1; // 0번부터 시작
		
		FGameplayTag ChosenTag;
		if (PlayerIndex == 0)
		{
			ChosenTag = FGameplayTag::RequestGameplayTag(FName("Class.Warrior.Berserker"));
		}
		else
		{
			ChosenTag = FGameplayTag::RequestGameplayTag(FName("Class.Magician.Sorceress"));
		}
		PS->SetSelectedClassTag(ChosenTag);
	}
}
