#include "UI/Widget/Player/Party/LA_PartyWidget.h"

#include "Components/VerticalBox.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerState/LA_PlayerState.h"
#include "UI/Widget/Player/Party/LA_PartyMemberSlot.h"

void ULA_PartyWidget::RefreshPartyList()
{
	if (!PartyMemberBox || !SlotClass) return;
	
	// 기존에 생성되어 있던 슬롯들 제거
	PartyMemberBox->ClearChildren();
	
	// 2. 내 PartyID 확인
	ALA_PlayerState* MyPS = Cast<ALA_PlayerState>(GetOwningPlayerState());
	if (!MyPS || !MyPS->GetPartyID().IsValid()) return;
	
	FGuid MyPartyID = MyPS->GetPartyID();
	
	// 3. 전체 플레이어를 순회하며 파티원 찾기
	if (AGameStateBase* GS = GetWorld()->GetGameState())
	{
		for (APlayerState* PS : GS->PlayerArray)
		{
			ALA_PlayerState* TargetPS = Cast<ALA_PlayerState>(PS);
			if (TargetPS && TargetPS->GetPartyID() == MyPartyID)
			{
				// 4. 슬롯 생성 및 데이터 주입
				ULA_PartyMemberSlot* NewSlot = CreateWidget<ULA_PartyMemberSlot>(GetWorld(),SlotClass);
				if (NewSlot)
				{
					NewSlot->SetupSlot(TargetPS);
					PartyMemberBox->AddChildToVerticalBox(NewSlot);
				}
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		this->RefreshPartyList();
	});
}
