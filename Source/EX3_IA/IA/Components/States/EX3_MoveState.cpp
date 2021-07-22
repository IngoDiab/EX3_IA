// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_MoveState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_MoveState::EnterState() const
{
}

UEX3_Transition* UEX3_MoveState::UpdateState() const
{
	if(!m_Brain) return Super::UpdateState();
	m_Brain->GetMovementSystem()->OnMoveToPos()->Broadcast();
	return Super::UpdateState();
}

void UEX3_MoveState::ExitState() const
{
}
