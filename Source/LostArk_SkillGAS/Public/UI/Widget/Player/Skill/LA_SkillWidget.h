#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LA_SkillWidget.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ULA_SkillWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 마우스 버튼을 눌렀을 때 실행
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// 마우스가 움직일 때 실행
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// 마우스 버튼을 뗏을 때 실행
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	// 마우스 버튼을 눌렀는지?
	bool bIsDragging = false;
	// 마우스 클릭 지점과 위젯 좌상단 사이의 거리 (오프셋)
	FVector2D DragOffset;
};
