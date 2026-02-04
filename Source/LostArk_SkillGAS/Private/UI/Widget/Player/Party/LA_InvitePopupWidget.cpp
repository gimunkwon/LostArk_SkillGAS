#include "UI/Widget/Player/Party/LA_InvitePopupWidget.h"

#include "Controller/Player/LA_PlayerController.h"

void ULA_InvitePopupWidget::OnAcceptClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("Party Invite Accepted"));
	
	// 컨트롤러를 통해 서버에 수락 신호 전달
	if (ALA_PlayerController* PC = Cast<ALA_PlayerController>(GetOwningPlayer()))
	{
		PC->Server_ReplyToInvite(InviterCharacter, true);
	}
	RemoveFromParent();
}

void ULA_InvitePopupWidget::OnDeclineClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("Party Invite Declined"));
	
	// 컨트롤러를 통해 서버에 거절 신호 전달
	if (ALA_PlayerController* PC = Cast<ALA_PlayerController>(GetOwningPlayer()))
	{
		PC->Server_ReplyToInvite(InviterCharacter, false);
	}
	RemoveFromParent();
}
