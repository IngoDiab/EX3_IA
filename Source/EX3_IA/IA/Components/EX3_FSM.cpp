// Fill out your copyright notice in the Description page of Project Settings.


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

// Sets default values for this component's properties
UEX3_FSM::UEX3_FSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEX3_FSM::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
}


// Called every frame
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
	//Create IDLEState
	UEX3_IDLEState* _idleState = NewObject<UEX3_IDLEState>();
	m_States.Add(_idleState);

	//Create ChaseState
	UEX3_ChaseState* _chaseState = NewObject<UEX3_ChaseState>();
	m_States.Add(_chaseState);

	UEX3_WaitState* _waitState = NewObject<UEX3_WaitState>();
	m_States.Add(_waitState);

	//Create IDLE/Chase Transition
	UEX3_IDLE_To_Chase* _IDLE_To_Chase = NewObject<UEX3_IDLE_To_Chase>();
	_IDLE_To_Chase->InitTransition(*this, *_chaseState);
	_idleState->AddTransition(*_IDLE_To_Chase);
	
	UEX3_Chase_To_IDLE* _Chase_To_IDLE = NewObject<UEX3_Chase_To_IDLE>();
	_Chase_To_IDLE->InitTransition(*this, *_idleState);
	_chaseState->AddTransition(*_Chase_To_IDLE);

	//Create Chase/Wait Transition
	UEX3_Chase_To_Wait* _Chase_To_Wait = NewObject<UEX3_Chase_To_Wait>();
	_Chase_To_Wait->InitTransition(*this, *_waitState);
	_chaseState->AddTransition(*_Chase_To_Wait);

	UEX3_Wait_To_Chase* _Wait_To_Chase = NewObject<UEX3_Wait_To_Chase>();
	_Wait_To_Chase->InitTransition(*this, *_chaseState);
	_waitState->AddTransition(*_Wait_To_Chase);

	//Init all state with brain
	for (UEX3_State* _state : m_States)
		_state->InitState(*m_Brain);

	SetStartState(*_idleState);
}

void UEX3_FSM::SetStartState(UEX3_State& _state)
{
	//Init First State
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

