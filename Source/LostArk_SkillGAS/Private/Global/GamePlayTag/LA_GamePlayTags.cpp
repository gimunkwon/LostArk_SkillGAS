#include "Global/GamePlayTag/LA_GamePlayTags.h"

#include "GameplayTagsManager.h"
#include "LostArk_SkillGAS/LostArk_SkillGAS.h"

FLA_GamePlayTags FLA_GamePlayTags::GamePlayTags;

void FLA_GamePlayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	// 에디터에서 Class.Warrior.xx 로 보이게 등록
#pragma region PlayerClass
	/*----------전사----------*/
	ADD_TAG(GamePlayTags.Class_Warrior, "Class.Warrior");
	ADD_TAG(GamePlayTags.Class_Warrior_Berserker, "Class.Warrior.Berserker");
	ADD_TAG(GamePlayTags.Class_Warrior_HolyKnight, "Class.Warrior.HolyKnight");
	/*----------마법사----------*/
	ADD_TAG(GamePlayTags.Class_Magician, "Class.Magician");
	ADD_TAG(GamePlayTags.Class_Magician_Sorceress, "Class.Magician.Sorceress");
	ADD_TAG(GamePlayTags.Class_Magician_Summoner, "Class.Magician.Summoner");
#pragma endregion 
#pragma region Monster
	/*----------군단장----------*/
	ADD_TAG(GamePlayTags.Monster_Commander, "Monster.Commander");
	ADD_TAG(GamePlayTags.Monster_Commander_Karmen, "Monster.Commander.Karmen");
	/*----------일반몬스터----------*/
	ADD_TAG(GamePlayTags.Monster_Normal, "Monster.Normal");
	ADD_TAG(GamePlayTags.Monster_Normal_Goblin, "Monster.Normal.Goblin");
#pragma endregion
	
#pragma region Party
	// 파티
	ADD_TAG(GamePlayTags.State_Party, "State.Party");
	ADD_TAG(GamePlayTags.State_Party_Leader, "State.Party.Leader");
	ADD_TAG(GamePlayTags.State_Party_Member, "State.Party.Member");
#pragma endregion
	
#pragma region Abilities
	ADD_TAG(GamePlayTags.Ability_Dash, "Ability.Dash");
#pragma endregion
	
	
	UE_LOG(LogTemp,Warning,TEXT("========InitializeNativeTags ON========"));
}

