// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_ChaseState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_ChaseState::InitState(UEX3_Brain& _brain)
{
	Super::InitState(_brain);
	m_MoveSystem = _brain.GetMovementSystem();
}

void UEX3_ChaseState::EnterState()
{
	m_MoveSystem->SetIsInChase(true);
}

UEX3_Transition* UEX3_ChaseState::UpdateState()
{
	if(!m_Brain) return Super::UpdateState();
	UpdateMove();
	return Super::UpdateState();
}

void UEX3_ChaseState::ExitState()
{
	m_MoveSystem->SetIsInChase(false);
}

void UEX3_ChaseState::UpdateMove() const
{
	if (!m_MoveSystem)return;
	m_MoveSystem->UpdateMovementSystem();
}
