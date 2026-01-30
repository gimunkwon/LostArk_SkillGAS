// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameInstance/LA_GameInstance.h"

#include "Kismet/KismetSystemLibrary.h"

void ULA_GameInstance::Init()
{
	Super::Init();
	
	// 모든 창(서버/클라이언트)의 프레임을 60으로 고정
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("t.MaxFPS 60"));
	
	// FPS 표시
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("Stat FPS"));
	
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized: FPS Fixed to 60"));
}
