#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Base/LA_BaseCharacter.h"
#include "LA_ContextMenuWidget.generated.h"

// 델리게이트 선언 (어떤 캐릭터를 초대할지 Target 정보를 담음)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInviteButtonClicked, ALA_BaseCharacter*, Target);


class ALA_BaseCharacter;

UCLASS()
class LOSTARK_SKILLGAS_API ULA_ContextMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnInviteButtonClicked OnInviteRequested; // 델리게이트 인스턴스
	
	// Getter,Setter 함수
	void SetTargetCharacter(ALA_BaseCharacter* Target) {TargetCharacter = Cast<ALA_BaseCharacter>(Target);};
	ALA_BaseCharacter* GetTargetCharacter() const{return TargetCharacter;};
	
	// 블루 프린트의 버튼 클릭 이벤트와 연결될 함수
	UFUNCTION(BlueprintCallable, Category="Party")
	void OnInviteButtonClicked();
protected:
	// 컨텍스트 메뉴가 들때 어떤플레이어를 찍었는지 저장
	UPROPERTY(BlueprintReadOnly, Category="Party", meta=(ExposeOnSpawn = true))
	TObjectPtr<ALA_BaseCharacter> TargetCharacter;
};
