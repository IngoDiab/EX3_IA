// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_ChaseState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_FSM.h"
#include"EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_ChaseState::InitState(UEX3_Brain& _brain)
{
	Super::InitState(_brain);
	m_MoveSystem = _brain.GetMovementSystem();
}

void UEX3_ChaseState::EnterState()
{
	if (!m_MoveSystem || !m_FSM)return;
	m_MoveSystem->SetMinDist(m_FSM->GetMaxDistChase());
	m_MoveSystem->SetIsLookingAtPlayer(false);
}

UEX3_Transition* UEX3_ChaseState::UpdateState()
{
	if(!m_Brain) return Super::UpdateState();
	UpdateMove();
	return Super::UpdateState();
}

void UEX3_ChaseState::ExitState()
{
	if (!m_MoveSystem)return;
	m_MoveSystem->SetIsLookingAtPlayer(true);
}

void UEX3_ChaseState::UpdateMove() const
{
	if (!m_MoveSystem)return;
	m_MoveSystem->UpdateMovementSystem();
}
