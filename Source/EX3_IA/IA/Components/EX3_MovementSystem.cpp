#include "EX3_MovementSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



#include "DrawDebugHelpers.h"

UEX3_MovementSystem::UEX3_MovementSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEX3_MovementSystem::PostInitProperties()
{
	Super::PostInitProperties();
}

void UEX3_MovementSystem::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
}

void UEX3_MovementSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEX3_MovementSystem::InitComponent()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	m_Controller = UAIBlueprintHelperLibrary::GetAIController(m_Owner);
	m_PosToMove = m_Owner->GetActorLocation();
}

bool UEX3_MovementSystem::IsAtPosTarget()
{
	return IsAtPos(m_PosToMove, m_MinDist);
}

bool UEX3_MovementSystem::IsAtPos(const FVector _pos, const float _minDist)
{
	if (!m_Owner) return true;
	const FVector _currentPos = m_Owner->GetActorLocation();
	const float _dist = FVector::Distance(_currentPos, _pos);
	return _dist < _minDist;
}

void UEX3_MovementSystem::UpdateMovementSystem()
{
	if (IsAtPosTarget()) onPosReached.Broadcast();
	else onMoveToPos.Broadcast(); 
}

void UEX3_MovementSystem::MoveToPos()
{
	if (!m_CanMove || !m_Controller)return;
	m_Controller->MoveToLocation(m_PosToMove);
	m_NextPathPoint = UAIBlueprintHelperLibrary::GetCurrentPathPoints(m_Controller)[1] + FVector::UpVector * m_Owner->GetScaledCapsuleHalfHeight();
	DrawDebugSphere(GetWorld(), m_NextPathPoint, 20, 100, FColor::Blue);
	DrawDebugSphere(GetWorld(), m_NextPathPoint, 10, 100, FColor::Red);
}

void UEX3_MovementSystem::RotateToPos()
{
	if (!m_CanRotate || !m_Owner)return;
	const FVector _posToLook = m_IsLookingAtPlayer ? FVector(m_PosToMove.X, m_PosToMove.Y, m_Owner->GetActorLocation().Z) : m_NextPathPoint;
	if (!m_IsLookingAtPlayer && IsAtPos(m_NextPathPoint, m_MinDistForPathPoint)) return;
	const FRotator _lookAtRotation = UKismetMathLibrary::FindLookAtRotation(m_Owner->GetActorLocation(), _posToLook);
	const FRotator _newRotation = UKismetMathLibrary::RInterpTo_Constant(m_Owner->GetActorRotation(), _lookAtRotation, GetWorld()->DeltaTimeSeconds, m_SpeedRotate);
	m_Owner->SetActorRotation(_newRotation);
}

void UEX3_MovementSystem::GoToPos()
{
	MoveToPos();
	RotateToPos();
}

void UEX3_MovementSystem::Stop()
{
	m_Controller->StopMovement();
	RotateToPos();
}

