#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LA_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALA_PlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// Default MappingContext
	UPROPERTY(EditAnywhere,Category="Input|MappingContext")
	UInputMappingContext* DefaultMappingContext;
	// InputAction
	UPROPERTY(EditAnywhere,Category="Input|InputAction")
	UInputAction* IA_ClickToMove;
	// InputAction Binding Function
	void OnInputStarted();
	
	
};
