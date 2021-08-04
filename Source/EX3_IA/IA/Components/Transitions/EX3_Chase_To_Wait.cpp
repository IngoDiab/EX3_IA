#include "EX3_Chase_To_Wait.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"
#include "EX3_IA/IA/Components/EX3_Brain.h"
#include "EX3_IA/IA/Components/EX3_MovementSystem.h"

void UEX3_Chase_To_Wait::InitTransition(UEX3_Brain& _brain, UEX3_State& _nextState)
{
	Super::InitTransition(_brain, _nextState);
	m_MoveSystem = _brain.GetMovementSystem();
}

void UEX3_Chase_To_Wait::EnterTransition() const
{
	if (!m_MoveSystem || !m_FSM)return;
	m_MoveSystem->SetMinDist(m_FSM->GetMaxDistCombat());
}

void UEX3_Chase_To_Wait::ExitTransition() const
{
}

bool UEX3_Chase_To_Wait::CheckCondition() const
{
	if (!m_FSM) return false;
	return m_FSM->IsAtPos();
}
