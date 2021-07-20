// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_Brain.h"
#include "EX3_FSM.h"
#include "EX3_DetectionSystem.h"
#include "EX3_MovementSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"

// Sets default values for this component's properties
UEX3_Brain::UEX3_Brain()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CreateComponents();
}


// Called when the game starts
void UEX3_Brain::BeginPlay()
{
	Super::BeginPlay();
	InitEventsComponents();
}

void UEX3_Brain::PostInitProperties()
{
	Super::PostInitProperties();
	InitOwner();
}


// Called every frame
void UEX3_Brain::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	onUpdateBrain.Broadcast();
}

void UEX3_Brain::CreateComponents()
{
	//Create FSM
	m_FSM = CreateDefaultSubobject<UEX3_FSM>(TEXT("FSM"));
	//Create Detection System
	m_DetectionSystem = CreateDefaultSubobject<UEX3_DetectionSystem>(TEXT("DetectionSystem"));
	//Create Movement System
	m_MovementSystem = CreateDefaultSubobject<UEX3_MovementSystem>(TEXT("MovementSystem"));
}

void UEX3_Brain::InitOwner()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	AttachComponentsToOwner();
}

void UEX3_Brain::AttachComponentsToOwner()
{
	if (!m_Owner)return;
	m_Owner->AddOwnedComponent(m_FSM);
	m_Owner->AddOwnedComponent(m_DetectionSystem);
	m_Owner->AddOwnedComponent(m_MovementSystem);
}

void UEX3_Brain::InitEventsComponents()
{
	if (!m_DetectionSystem || !m_MovementSystem) return;
	m_DetectionSystem->OnPlayerTracked()->AddLambda([this](FVector _pos) 
	{
		m_MovementSystem->SetPosToMove(_pos);
		m_MovementSystem->MoveToPos();
		m_MovementSystem->RotateToPos();
	});
}

