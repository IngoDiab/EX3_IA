// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_DetectionSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UEX3_DetectionSystem::UEX3_DetectionSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEX3_DetectionSystem::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
}


// Called every frame
void UEX3_DetectionSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	VisionDetection();
}

void UEX3_DetectionSystem::InitComponent()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	m_ActorToIgnore = TArray<AActor*>();
	m_ActorToIgnore.Add(m_Owner);
	m_OwnerEyesLocation = m_Owner->GetEyesLocation();
}

bool UEX3_DetectionSystem::VisionLineTrace(const float _angle)
{
	if (!m_OwnerEyesLocation) return false;
	FHitResult _hit;
	const FVector _start = m_OwnerEyesLocation->GetComponentLocation();
	const FVector _rotatedForward = m_OwnerEyesLocation->GetForwardVector().RotateAngleAxis(_angle, m_OwnerEyesLocation->GetUpVector());
	const FVector _end = _start+ _rotatedForward * m_DistanceVision;
	const bool _hasHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), _start, _end, ETraceTypeQuery::TraceTypeQuery3, true, m_ActorToIgnore, EDrawDebugTrace::ForOneFrame, _hit, true);
	if (!_hasHit) return false;
	return Cast<ACharacter>(_hit.Actor) != nullptr;
}

void UEX3_DetectionSystem::VisionDetection()
{
	const float _angleLeft = -m_AngleVision / 2;
	const float _angleRight = m_AngleVision / 2;
	bool _hit = false;
	for (int i = _angleLeft; i < _angleRight; i++) 
	{
		_hit |= VisionLineTrace(i);
		//if (_hit)break;
	}
	if (_hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("See"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Lost"));
}

