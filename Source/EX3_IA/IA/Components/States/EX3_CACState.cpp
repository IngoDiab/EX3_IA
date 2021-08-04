#include "EX3_CACState.h"

#include"EX3_IA/IA/Components/EX3_Brain.h"
#include"EX3_IA/IA/Components/EX3_FSM.h"
#include"EX3_IA/IA/Components/EX3_CACSystem.h"
#include"EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_CACState::InitState(UEX3_Brain& _brain)
{
	Super::InitState(_brain);
	m_MoveSystem = _brain.GetMovementSystem();
	m_CACSystem = _brain.GetCACSystem();
}

void UEX3_CACState::EnterState()
{
	Attack();
}

UEX3_Transition* UEX3_CACState::UpdateState()
{
	if (!m_MoveSystem) return Super::UpdateState();
	m_MoveSystem->RotateToPos();
	return Super::UpdateState();
}

void UEX3_CACState::ExitState()
{
	if (!m_CACSystem)return;
	m_CACSystem->ResetCombo();
}

void UEX3_CACState::Attack()
{
	if (!m_CACSystem)return;
	m_CACSystem->ChooseTypeAttack();
	m_CACSystem->Attack();
}
