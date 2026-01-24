#include "Global/GamePlayTag/LA_GamePlayTags.h"

#include "GameplayTagsManager.h"

FLA_GamePlayTags FLA_GamePlayTags::GamePlayTags;

void FLA_GamePlayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	// 에디터에서 Class.Warrior.xx 로 보이게 등록
#pragma region PlayerClass
	/*----------전사----------*/
	GamePlayTags.Class_Warrior = Manager.AddNativeGameplayTag(FName("Class.Warrior"));
	GamePlayTags.Class_Warrior_Berserker = Manager.AddNativeGameplayTag(FName("Class.Warrior.Berserker"));
	GamePlayTags.Class_Warrior_HolyKnight = Manager.AddNativeGameplayTag(FName("Class.Warrior.HolyKnight"));
	/*----------마법사----------*/
	GamePlayTags.Class_Magician = Manager.AddNativeGameplayTag(FName("Class.Magician"));
	GamePlayTags.Class_Magician_Sorceress = Manager.AddNativeGameplayTag(FName("Class.Magician.Sorceress"));
	GamePlayTags.Class_Magician_Summoner = Manager.AddNativeGameplayTag(FName("Class.Magician.Summoner"));
#pragma endregion 
#pragma region Monster
	/*----------군단장----------*/
	GamePlayTags.Monster_Commander = Manager.AddNativeGameplayTag(FName("Monster.Commander"));
	GamePlayTags.Monster_Commander_Karmen = Manager.AddNativeGameplayTag(FName("Monster.Commander.Karmen"));
	/*----------일반몬스터----------*/
	GamePlayTags.Monster_Normal = Manager.AddNativeGameplayTag(FName("Monster.Normal"));
	GamePlayTags.Monster_Normal_Goblin = Manager.AddNativeGameplayTag(FName("Monster.Normal.Goblin"));
#pragma endregion
	
	UE_LOG(LogTemp,Warning,TEXT("========InitializeNativeTags ON========"));
}
