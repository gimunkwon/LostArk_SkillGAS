#pragma once

#include "CoreMinimal.h"
#include "Character/Base/LA_BaseCharacter.h"
#include "LA_BasePlayer.generated.h"

class ULA_BaseClassDA;
class ULA_ClassAttributeset;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LOSTARK_SKILLGAS_API ALA_BasePlayer : public ALA_BaseCharacter
{
	GENERATED_BODY()
public:
	ALA_BasePlayer();
	// GAS 초기화
	virtual void InitAbilityActorInfo() override;
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data|DataAsset")
	TObjectPtr<ULA_BaseClassDA> BaseClassDA;
	
#pragma region Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera | SpringArm")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera | Camera")
	UCameraComponent* TopDownCamera;
#pragma endregion
#pragma region AttributeSet
	UPROPERTY()
	TObjectPtr<ULA_ClassAttributeset> ClassAttributeSet;
#pragma endregion
#pragma region CharacterMesh
	
#pragma endregion
};
