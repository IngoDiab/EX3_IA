// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EX3_State.h"
#include "EX3_WaitState.generated.h"

/**
 * 
 */
UCLASS()
class EX3_IA_API UEX3_WaitState : public UEX3_State
{
	GENERATED_BODY()

	UPROPERTY() float m_TimeToWait = 3;
	UPROPERTY() float m_Timer = 0;

public:
	void EnterState() override;
	UEX3_Transition* UpdateState() override;
	void ExitState() override;

	void GetRandomTimeToWait();
	void UpdateTimer();
};
