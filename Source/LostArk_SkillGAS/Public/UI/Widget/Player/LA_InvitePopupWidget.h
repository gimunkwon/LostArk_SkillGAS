#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LA_InvitePopupWidget.generated.h"

class ALA_BaseCharacter;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_InvitePopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 나를 초대한 사람 정보(팝업 생성 시 전달 받음)
	UPROPERTY(BlueprintReadOnly, Category="Party")
	TObjectPtr<ALA_BaseCharacter> InviterCharacter;
	
	// 수락 버튼 클릭 시
	UFUNCTION(BlueprintCallable, Category="Party")
	void OnAcceptClicked();
	
	// 거절 버튼 클릭시
	UFUNCTION(BlueprintCallable, Category="Party")
	void OnDeclineClicked();
};
