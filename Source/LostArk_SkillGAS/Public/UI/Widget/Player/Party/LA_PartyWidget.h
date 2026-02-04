#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LA_PartyWidget.generated.h"

class ULA_PartyMemberSlot;
class UVerticalBox;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_PartyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 파티 리스트를 갱신하는 함수
	void RefreshPartyList();
	
protected:
	// 슬롯들이 쌓일 공간
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> PartyMemberBox;
	
	// 생성할 슬롯 위젯 클래스
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<ULA_PartyMemberSlot> SlotClass;
};
