#include "UI/Widget/Player/Skill/LA_SkillWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/SlateBlueprintLibrary.h"


FReply ULA_SkillWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	// 왼쪽 마우스 버튼인지 확인
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsDragging = true;
		
		// 현재 마우스의 절대 위치를 뷰포트 위치로 변환
		FVector2D MouseViewportPos;
		FVector2D Dummy;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), InMouseEvent.GetScreenSpacePosition(), MouseViewportPos, Dummy);
		
		// 현재 위젯의 절대 위치를 뷰포트 위치로 변환
		FVector2D WidgetViewportPos;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), InGeometry.GetAbsolutePosition(), WidgetViewportPos, Dummy);
		
		// 뷰포트 기준의 오프셋 계산
		DragOffset = MouseViewportPos - WidgetViewportPos;
		
		// 마우스 포커스를 이 위젯으로 고정
		return FReply::Handled().CaptureMouse(TakeWidget());
	}
	
	return FReply::Unhandled();
}

FReply ULA_SkillWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	
	if (bIsDragging)
	{
		// 현재 마우스의 절대 위치를 뷰포트 위치로 변환
		FVector2D MouseViewportPos;
		FVector2D Dummy;
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), InMouseEvent.GetScreenSpacePosition(), MouseViewportPos, Dummy);
		// 오프셋을 적용한 새로운 뷰포트 위치 계산
		FVector2D NewPosition = MouseViewportPos - DragOffset;
		
		
		// AddToViewport로 띄운 위젯은 이 함수를 사용
		SetPositionInViewport(NewPosition);
		
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply ULA_SkillWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsDragging = false;
		// 마우스 캡처 해제
		return FReply::Handled().ReleaseMouseCapture();
	}
	
	return FReply::Unhandled(); 
}
