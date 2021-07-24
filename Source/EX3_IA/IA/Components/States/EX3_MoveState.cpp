// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_MoveState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_MoveState::InitState(UEX3_Brain& _brain)
{
	Super::InitState(_brain);
	m_MoveSystem = _brain.GetMovementSystem();
}

void UEX3_MoveState::EnterState() const
{
	m_MoveSystem->SetIsInChase(true);
}

UEX3_Transition* UEX3_MoveState::UpdateState() const
{
	if(!m_Brain) return Super::UpdateState();
	UpdateMove();
	return Super::UpdateState();
}

void UEX3_MoveState::ExitState() const
{
	m_MoveSystem->SetIsInChase(false);
}

void UEX3_MoveState::UpdateMove() const
{
	if (!m_MoveSystem)return;
	UE_LOG(LogTemp, Warning, TEXT("UPDATE"));
	m_MoveSystem->UpdateMovementSystem();
}
