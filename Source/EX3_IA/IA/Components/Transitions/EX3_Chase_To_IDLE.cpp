#include "EX3_Chase_To_IDLE.h"

#include"EX3_IA/IA/Components/EX3_FSM.h"

void UEX3_Chase_To_IDLE::EnterTransition() const
{
}

void UEX3_Chase_To_IDLE::ExitTransition() const
{
}

bool UEX3_Chase_To_IDLE::CheckCondition() const
{
	return !m_FSM->IsPlayerSeen() && m_FSM->IsAtPos();
}