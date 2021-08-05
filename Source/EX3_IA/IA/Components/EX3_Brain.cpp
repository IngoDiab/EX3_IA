#include "EX3_Brain.h"

#include "EX3_FSM.h"
#include "EX3_DetectionSystem.h"
#include "EX3_MovementSystem.h"
#include "EX3_CACSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_IA/IA/Animation/EX3_IAAnimation.h"

UEX3_Brain::UEX3_Brain()
{
	PrimaryComponentTick.bCanEverTick = true;
	CreateComponents();
}

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
	InitBrainEvents();
	InitDetectionEvents();
	InitMovementEvents();
	InitCACEvents();
	InitAnimationsNotifyEvents();
}

void UEX3_Brain::InitBrainEvents()
{
	if (!m_DetectionSystem || !m_FSM)return;
	onUpdateBrain.AddLambda([this]()
	{
		m_DetectionSystem->UpdateVisualDetection();
		m_FSM->SetIsAtPos(m_MovementSystem->IsAtPos());
	});
}

void UEX3_Brain::InitDetectionEvents()
{
	if (!m_DetectionSystem || !m_FSM || !m_MovementSystem)return;
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
}

void UEX3_Brain::InitMovementEvents()
{
	if (!m_Animations || !m_MovementSystem)return;
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
}

void UEX3_Brain::InitCACEvents()
{
	if (!m_Animations || !m_CACSystem || !m_FSM)return;
	m_CACSystem->OnHeavyAttackCombo()->AddLambda([this]()
	{
		m_FSM->SetHasFinishedAttackState(false);
		m_Animations->SetIsHeavyAttacking(true);
	});

	m_CACSystem->OnLightAttackCombo()->AddLambda([this]()
	{
		m_FSM->SetHasFinishedAttackState(false);
		m_Animations->SetIsLightAttacking(true);
	});

	m_CACSystem->OnEndCombo()->AddLambda([this]()
	{
		EndCombo();
	});
}

void UEX3_Brain::InitAnimationsNotifyEvents()
{
	if (!m_Animations || !m_CACSystem)return;
	m_Animations->OnActivateDamage()->AddDynamic(this, &UEX3_Brain::ActivateDamage);
	m_Animations->OnLockAI()->AddDynamic(this, &UEX3_Brain::LockAI);
	m_Animations->OnEndComboDelegate()->AddDynamic(this, &UEX3_Brain::EndCombo);
}

void UEX3_Brain::ActivateDamage(const bool _dealDamage)
{
	if (!m_CACSystem) return;
	m_CACSystem->ActivateDamage(_dealDamage);
}

void UEX3_Brain::LockAI(const bool _lockAI)
{
	if (!m_FSM || !m_MovementSystem) return;
	m_FSM->SetIsInAttack(_lockAI);
	m_MovementSystem->SetCanRotate(!_lockAI);
}

void UEX3_Brain::EndCombo() 
{
	if (!m_FSM || !m_CACSystem || !m_Animations) return;
	m_FSM->SetHasFinishedAttackState(true);

	m_CACSystem->SetHeavyAttacking(false);
	m_CACSystem->SetLightAttacking(false);

	m_Animations->SetIsHeavyAttacking(false);
	m_Animations->SetIsLightAttacking(false);
}

