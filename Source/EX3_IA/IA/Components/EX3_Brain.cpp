// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_Brain.h"

#include "EX3_FSM.h"
#include "EX3_DetectionSystem.h"
#include "EX3_MovementSystem.h"
#include "EX3_CACSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_IA/IA/Animation/EX3_IAAnimation.h"

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
	InitOwner();
	InitAnimation();
	InitEventsComponents();
	m_FSM->StartFSM();
}

void UEX3_Brain::PostInitProperties()
{
	Super::PostInitProperties();
	
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
	//Create CAC System
	m_CACSystem = CreateDefaultSubobject<UEX3_CACSystem>(TEXT("CACSystem"));
}

void UEX3_Brain::InitOwner()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	AttachComponentsToOwner();
}

void UEX3_Brain::InitAnimation()
{
	if (!m_Owner)return;
	const USkeletalMeshComponent* _mesh = m_Owner->GetSkeletalMesh();
	if (!_mesh) return;
	m_Animations = Cast<UEX3_IAAnimation>(_mesh->GetAnimInstance());
}

void UEX3_Brain::AttachComponentsToOwner()
{
	if (!m_Owner)return;
	m_Owner->AddOwnedComponent(m_FSM);
	m_Owner->AddOwnedComponent(m_DetectionSystem);
	m_Owner->AddOwnedComponent(m_MovementSystem);
	m_Owner->AddOwnedComponent(m_CACSystem);
}

void UEX3_Brain::InitEventsComponents()
{
	if (!m_DetectionSystem || !m_MovementSystem || !m_CACSystem || !m_Animations) return;

	onUpdateBrain.AddLambda([this]()
	{
		m_DetectionSystem->UpdateVisualDetection();
		m_FSM->SetIsAtPos(m_MovementSystem->IsAtPos());
		//m_MovementSystem->UpdateIsAtPos();
	});

	/// <summary>
	/// //////////////////////////////////////////////////////////
	/// </summary>

	m_DetectionSystem->OnPlayerSpotted()->AddLambda([this]()
	{
		//UE_LOG(LogTemp, Warning, TEXT("AAAA"));
		m_DetectionSystem->SetIsSpotPlayer(true);
		m_FSM->SetIsPlayerSeen(true);
	});

	m_DetectionSystem->OnPlayerTracked()->AddLambda([this](FVector _targetPos)
	{
		m_MovementSystem->SetPosToMove(_targetPos);
	});

	m_DetectionSystem->OnPlayerLost()->AddLambda([this]()
	{
		m_DetectionSystem->ResetTarget();
		m_FSM->SetIsPlayerSeen(false);
	});

	/// <summary>
	/// //////////////////////////////////////////////////////
	/// </summary>

	m_MovementSystem->OnMoveToPos()->AddLambda([this]()
	{
		m_MovementSystem->GoToPos();
		m_Animations->SetIsMoving(true);
	});

	m_MovementSystem->OnPosReached()->AddLambda([this]()
	{
		m_MovementSystem->Stop();
		m_Animations->SetIsMoving(false);
	});


	/// <summary>
	/// ////////////////////////////////////////////////////
	/// </summary>
	m_CACSystem->OnHeavyAttackCombo()->AddLambda([this]()
	{
		m_Animations->SetIsHeavyAttacking(true);
	});

	m_CACSystem->OnLightAttackCombo()->AddLambda([this]()
	{
		m_Animations->SetIsLightAttacking(true);
	});

	m_CACSystem->OnEndCombo()->AddLambda([this]()
	{
		m_CACSystem->SetHeavyAttacking(false);
		m_CACSystem->SetLightAttacking(false);
		m_CACSystem->ResetNumberAttackInRow();

		m_Animations->SetIsHeavyAttacking(false);
		m_Animations->SetIsLightAttacking(false);
	});
}

