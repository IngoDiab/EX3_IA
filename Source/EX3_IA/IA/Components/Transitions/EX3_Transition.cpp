#include "EX3_Transition.h"

#include "EX3_IA/IA/Components/EX3_Brain.h"

void UEX3_Transition::InitTransition(UEX3_Brain& _brain, UEX3_State& _nextState)
{
	m_Brain = &_brain;
	if(m_Brain) m_FSM = _brain.GetFSM();
	m_NextState = &_nextState;
}
