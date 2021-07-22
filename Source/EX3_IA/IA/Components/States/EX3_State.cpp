// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_State.h"
#include "EX3_IA/IA/Components/Transitions/EX3_Transition.h"

void UEX3_State::InitState(UEX3_Brain& _brain)
{
	m_Brain = &_brain;
}

void UEX3_State::AddTransition(UEX3_Transition& _transition)
{
	m_Transitions.Add(&_transition);
}

UEX3_Transition* UEX3_State::UpdateState() const
{
	for (UEX3_Transition* _transition : m_Transitions)
		if (_transition->CheckCondition()) return _transition;
	return nullptr;
}
