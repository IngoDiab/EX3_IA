#include "EX3_FSM.h"

#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

#include "States/EX3_IDLEState.h"
#include "States/EX3_ChaseState.h"
#include "States/EX3_WaitState.h"
#include "States/EX3_CACState.h"

#include "Transitions/EX3_IDLE_To_Chase.h"
#include "Transitions/EX3_Chase_To_IDLE.h"
#include "Transitions/EX3_Chase_To_Wait.h"
#include "Transitions/EX3_Wait_To_Chase.h"
#include "Transitions/EX3_Wait_To_CAC.h"
#include "Transitions/EX3_CAC_To_Wait.h"
#include "Transitions/EX3_CAC_To_Chase.h"

UEX3_FSM::UEX3_FSM()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEX3_FSM::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
}

void UEX3_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFSM();
}

void UEX3_FSM::InitComponent()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	m_Brain = m_Owner->GetBrain();
	InitFSM();
}

void UEX3_FSM::InitFSM()
{
	UEX3_State* _firstState = CreateStates();
	
	//Init all state with brain
	for (UEX3_State* _state : m_States)
		_state->InitState(*m_Brain);

	SetStartState(*_firstState);
}

UEX3_State* UEX3_FSM::CreateStates()
{
	UEX3_IDLEState* _idleState = NewObject<UEX3_IDLEState>();
	m_States.Add(_idleState);

	UEX3_ChaseState* _chaseState = NewObject<UEX3_ChaseState>();
	m_States.Add(_chaseState);

	UEX3_WaitState* _waitState = NewObject<UEX3_WaitState>();
	m_States.Add(_waitState);

	UEX3_CACState* _CACState = NewObject<UEX3_CACState>();
	m_States.Add(_CACState);

	InitTransitionsFromIDLEState(*_idleState, *_chaseState);
	InitTransitionsFromChaseState(*_chaseState, *_idleState, *_waitState);
	InitTransitionsFromWaitState(*_waitState, *_chaseState, *_CACState);
	InitTransitionsFromCACState(*_CACState, *_waitState, *_chaseState);

	return _idleState;
}

void UEX3_FSM::InitTransitionsFromIDLEState(UEX3_IDLEState& _idleState, UEX3_ChaseState& _chaseState)
{
	UEX3_IDLE_To_Chase* _IDLE_To_Chase = NewObject<UEX3_IDLE_To_Chase>();
	_IDLE_To_Chase->InitTransition(*m_Brain, _chaseState);
	_idleState.AddTransition(*_IDLE_To_Chase);
}

void UEX3_FSM::InitTransitionsFromChaseState(UEX3_ChaseState& _chaseState, UEX3_IDLEState& _idleState, UEX3_WaitState& _waitState)
{
	UEX3_Chase_To_IDLE* _Chase_To_IDLE = NewObject<UEX3_Chase_To_IDLE>();
	_Chase_To_IDLE->InitTransition(*m_Brain, _idleState);
	_chaseState.AddTransition(*_Chase_To_IDLE);

	UEX3_Chase_To_Wait* _Chase_To_Wait = NewObject<UEX3_Chase_To_Wait>();
	_Chase_To_Wait->InitTransition(*m_Brain, _waitState);
	_chaseState.AddTransition(*_Chase_To_Wait);
}

void UEX3_FSM::InitTransitionsFromWaitState(UEX3_WaitState& _waitState, UEX3_ChaseState& _chaseState, UEX3_CACState& _CACState)
{
	UEX3_Wait_To_Chase* _Wait_To_Chase = NewObject<UEX3_Wait_To_Chase>();
	_Wait_To_Chase->InitTransition(*m_Brain, _chaseState);
	_waitState.AddTransition(*_Wait_To_Chase);

	UEX3_Wait_To_CAC* _Wait_To_CAC = NewObject<UEX3_Wait_To_CAC>();
	_Wait_To_CAC->InitTransition(*m_Brain, _CACState);
	_waitState.AddTransition(*_Wait_To_CAC);
}

void UEX3_FSM::InitTransitionsFromCACState(UEX3_CACState& _CACState, UEX3_WaitState& _waitState, UEX3_ChaseState& _chaseState)
{
	UEX3_CAC_To_Wait* _CAC_To_Wait = NewObject<UEX3_CAC_To_Wait>();
	_CAC_To_Wait->InitTransition(*m_Brain, _waitState);
	_CACState.AddTransition(*_CAC_To_Wait);

	UEX3_CAC_To_Chase* _CAC_To_Chase = NewObject<UEX3_CAC_To_Chase>();
	_CAC_To_Chase->InitTransition(*m_Brain, _chaseState);
	_CACState.AddTransition(*_CAC_To_Chase);
}

void UEX3_FSM::SetStartState(UEX3_State& _state)
{
	m_CurrentState = &_state;
	if (m_CurrentState) m_CurrentState->EnterState();
}

void UEX3_FSM::UpdateFSM()
{
	if (!m_IsStarted || !m_CurrentState)return;
	const UEX3_Transition* _nextTransition = m_CurrentState->UpdateState();
	if (!_nextTransition)return;
	SetNextState(_nextTransition);
}

void UEX3_FSM::SetNextState(const UEX3_Transition* _transition)
{
	if (!_transition)return;
	if (m_CurrentState) m_CurrentState->ExitState();
	_transition->EnterTransition();
	_transition->ExitTransition();
	UEX3_State* _nextState = _transition->GetNextState();
	if (!_nextState) return;
	m_CurrentState = _nextState;
	if (m_CurrentState) m_CurrentState->EnterState();
}

