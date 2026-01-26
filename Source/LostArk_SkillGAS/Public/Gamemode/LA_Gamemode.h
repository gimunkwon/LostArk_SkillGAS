#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LA_Gamemode.generated.h"

UCLASS()
class LOSTARK_SKILLGAS_API ALA_Gamemode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
