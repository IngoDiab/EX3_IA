// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_FSM.h"

#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

#include "States/EX3_IDLEState.h"
#include "States/EX3_MoveState.h"

#include "Transitions/EX3_IDLE_To_Move.h"
#include "Transitions/EX3_Move_To_IDLE.h"

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

	//Create MoveState
	UEX3_MoveState* _moveState = NewObject<UEX3_MoveState>();
	m_States.Add(_moveState);

	//Create IDLE->Move Transition
	UEX3_IDLE_To_Move* _IDLE_To_Move = NewObject<UEX3_IDLE_To_Move>();
	_IDLE_To_Move->InitTransition(*this, *_moveState);
	_idleState->AddTransition(*_IDLE_To_Move);
	
	UEX3_Move_To_IDLE* _Move_To_IDLE = NewObject<UEX3_Move_To_IDLE>();
	_Move_To_IDLE->InitTransition(*this, *_idleState);
	_moveState->AddTransition(*_Move_To_IDLE);

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

