// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_CACState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_CACSystem.h"

void UEX3_CACState::InitState(UEX3_Brain& _brain)
{
	Super::InitState(_brain);
	m_CACSystem = _brain.GetCACSystem();
}

void UEX3_CACState::EnterState()
{
	if (!m_CACSystem)return;
	m_CACSystem->ChooseTypeAttack();
	m_CACSystem->Attack();
}

UEX3_Transition* UEX3_CACState::UpdateState()
{
	return Super::UpdateState();
}

void UEX3_CACState::ExitState()
{

}