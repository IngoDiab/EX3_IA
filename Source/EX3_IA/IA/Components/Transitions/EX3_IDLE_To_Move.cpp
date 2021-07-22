// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_IDLE_To_Move.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"

void UEX3_IDLE_To_Move::EnterTransition() const
{
}

void UEX3_IDLE_To_Move::ExitTransition() const
{
}

bool UEX3_IDLE_To_Move::CheckCondition() const
{
	return m_FSM->IsPlayerSeen();
}
