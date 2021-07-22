// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_Transition.h"

void UEX3_Transition::InitTransition(UEX3_FSM& _fsm, UEX3_State& _nextState)
{
	m_FSM = &_fsm;
	m_NextState = &_nextState;
}
