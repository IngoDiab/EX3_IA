// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_DetectionSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

#include "EX3_MovementSystem.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UEX3_DetectionSystem::UEX3_DetectionSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UEX3_DetectionSystem::PostInitProperties()
{
	Super::PostInitProperties();
}

// Called when the game starts
void UEX3_DetectionSystem::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
	//onPlayerSpottedDelegate.AddDynamic(this, &UEX3_DetectionSystem::SpotTarget);
}


// Called every frame
void UEX3_DetectionSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/*void UEX3_DetectionSystem::InitEvents()
{
	onPlayerSpottedDelegate.AddDynamic(this, &UEX3_DetectionSystem::SpotTarget);

	onPlayerSpotted.AddLambda([this]()
	{
		m_IsPlayerSpotted = true;
	});

	onPlayerLost.AddLambda([this]()
	{
		m_PlayerSpotted = nullptr;
		m_IsPlayerSpotted = false;
	});

	if (!m_Brain)return;
	m_Brain->OnUpdateBrain()->AddLambda([this]()
	{
		UpdateVisualDetection();
	});
}*/

void UEX3_DetectionSystem::InitComponent()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	//m_Brain = m_Owner->GetBrain();
	m_ActorToIgnore = TArray<AActor*>();
	m_ActorToIgnore.Add(m_Owner);
	m_OwnerEyesLocation = m_Owner->GetEyesLocation();
	//InitEvents();
}

void UEX3_DetectionSystem::UpdateVisualDetection()
{
	const bool _seeEnnemy = VisionDetection();
	//if (_seeEnnemy && !m_IsPlayerSpotted) onPlayerSpottedDelegate.Broadcast(m_PlayerSpotted);
	if (_seeEnnemy && !m_IsPlayerSpotted) onPlayerSpotted.Broadcast();
	else if (_seeEnnemy && m_IsPlayerSpotted && m_PlayerSpotted) onPlayerTracked.Broadcast(m_PlayerSpotted->GetActorLocation());
	else if (!_seeEnnemy && m_IsPlayerSpotted) onPlayerLost.Broadcast();
}

bool UEX3_DetectionSystem::VisionDetection()
{
	const float _angleLeft = -m_AngleVision / 2;
	const float _angleRight = m_AngleVision / 2;
	bool _hasHit = false;
	for (int i = _angleLeft; i < _angleRight; i++) 
	{
		_hasHit |= VisionLineTrace(i);
		//if (_hasHit)break;
	}
	return _hasHit;
}

bool UEX3_DetectionSystem::VisionLineTrace(const float _angle)
{
	if (!m_OwnerEyesLocation) return false;
	FHitResult _hit;
	const FVector _start = m_OwnerEyesLocation->GetComponentLocation();
	const FVector _rotatedForward = m_OwnerEyesLocation->GetForwardVector().RotateAngleAxis(_angle, m_OwnerEyesLocation->GetUpVector());
	const FVector _end = _start + _rotatedForward * m_DistanceVision;
	const bool _hasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), _start, _end, ETraceTypeQuery::TraceTypeQuery3, true, m_ActorToIgnore, EDrawDebugTrace::ForOneFrame, _hit, true);
	if (!_hasHit) return false;
	ACharacter* _target = Cast<ACharacter>(_hit.Actor);
	if (!_target) return false;
	RegisterTarget(_target);
	return true;
}

/*void UEX3_DetectionSystem::SpotTarget(ACharacter* _target)
{
	UE_LOG(LogTemp, Warning, TEXT("SPOT"));
	onPlayerSpotted.Broadcast();
}*/

void UEX3_DetectionSystem::RegisterTarget(ACharacter* _target)
{
	if (m_PlayerSpotted)return;
	m_PlayerSpotted = _target;
}

void UEX3_DetectionSystem::ResetTarget()
{
	m_PlayerSpotted = nullptr;
	m_IsPlayerSpotted = false;
}

