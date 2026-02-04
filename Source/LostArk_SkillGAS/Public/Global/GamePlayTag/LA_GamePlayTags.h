#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LA_GamePlayTags.generated.h"

USTRUCT(BlueprintType)
struct FLA_GamePlayTags
{
public:
	GENERATED_BODY()
	
	FORCEINLINE static const FLA_GamePlayTags& Get() {return GamePlayTags;}
#pragma region PlayerClass
	#pragma region Warrior
	/*--------전사계열 태그--------*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class")
	FGameplayTag Class_Warrior;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class | Job")
	FGameplayTag Class_Warrior_Berserker;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class | Job")
	FGameplayTag Class_Warrior_HolyKnight;
	/*--------마법사계열 태그--------*/
#pragma endregion
	#pragma region Magician
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class")
	FGameplayTag Class_Magician;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class | Job")
	FGameplayTag Class_Magician_Sorceress;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Class | Job")
	FGameplayTag Class_Magician_Summoner;
#pragma endregion
#pragma endregion 
	
#pragma region MonsterClass
	#pragma region Commander
	/*--------군단장계열 태그--------*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster")
	FGameplayTag Monster_Commander;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster | Level")
	FGameplayTag Monster_Commander_Karmen;
	#pragma endregion 
	#pragma region Normal
	/*--------일반계열 태그--------*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster")
	FGameplayTag Monster_Normal;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster | Level")
	FGameplayTag Monster_Normal_Goblin;
	#pragma endregion
#pragma endregion
	
#pragma region Party
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Party")
	FGameplayTag State_Party;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Party | Level")
	FGameplayTag State_Party_Leader; // 파티장
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Party | Level")
	FGameplayTag State_Party_Member; // 파티원
#pragma endregion 
	
#pragma region Abilities
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Abilities")
	FGameplayTag Ability_Dash;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Abilities")
	FGameplayTag Ability_Dash_Warrior;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Abilities")
	FGameplayTag Ability_Dash_Magician;
#pragma endregion 
	// 초기화 함수
	static void InitializeNativeTags();
private:
	static FLA_GamePlayTags GamePlayTags;
};
