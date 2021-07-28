// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_IDLE_To_Chase.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"

void UEX3_IDLE_To_Chase::EnterTransition() const
{
}

void UEX3_IDLE_To_Chase::ExitTransition() const
{
}

bool UEX3_IDLE_To_Chase::CheckCondition() const
{
	if (!m_FSM) return false;
	return m_FSM->IsPlayerSeen();
}
