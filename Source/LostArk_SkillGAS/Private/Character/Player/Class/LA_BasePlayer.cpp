#include "Character/Player/Class/LA_BasePlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ALA_BasePlayer::ALA_BasePlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 600.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetRelativeRotation(FRotator(60.f,0.f,0.f));
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	TopDownCamera->SetupAttachment(SpringArmComponent);
	
}


void ALA_BasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALA_BasePlayer::InitPlayerASC()
{
}



