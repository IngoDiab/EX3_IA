// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_WaitState.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"

#include "Kismet/KismetMathLibrary.h"

void UEX3_WaitState::EnterState()
{
	if (!m_FSM)return;
	m_FSM->SetIsWaiting(true);
	GetRandomTimeToWait();
}

UEX3_Transition* UEX3_WaitState::UpdateState()
{
	UpdateTimer();
	return Super::UpdateState();
}

void UEX3_WaitState::ExitState()
{
	m_Timer = 0;
}

void UEX3_WaitState::GetRandomTimeToWait()
{
	if (!m_FSM || !m_FSM->GetUseRandomWaitingTime()) return;
	m_TimeToWait = UKismetMathLibrary::RandomFloatInRange(.1f, 5);
}

void UEX3_WaitState::UpdateTimer()
{
	if (!m_FSM)return;
	if (m_Timer < m_TimeToWait)
		m_Timer += 0.01f;
	else
		m_FSM->SetIsWaiting(false);
}
