#include "UI/Widget/Player/LA_ContextMenuWidget.h"

#include "Controller/Player/LA_PlayerController.h"
#include "UI/HUD/LA_HUD.h"

void ULA_ContextMenuWidget::OnInviteButtonClicked()
{
	// 클릭을 당한 플레이어에게 InvitePopupWidget을 띄워라
	if (TargetCharacter && OnInviteRequested.IsBound())
	{
		OnInviteRequested.Broadcast(TargetCharacter);
	}
	RemoveFromParent();
}
