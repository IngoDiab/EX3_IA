// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_Wait_To_CAC.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"

void UEX3_Wait_To_CAC::EnterTransition() const
{
}

void UEX3_Wait_To_CAC::ExitTransition() const
{
}

bool UEX3_Wait_To_CAC::CheckCondition() const
{
	if (!m_FSM) return false;
	return !m_FSM->IsWaiting() && m_FSM->IsPlayerSeen();
}

