// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_MovementSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values for this component's properties
UEX3_MovementSystem::UEX3_MovementSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEX3_MovementSystem::PostInitProperties()
{
	Super::PostInitProperties();
}

// Called when the game starts
void UEX3_MovementSystem::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();}


// Called every frame
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

bool UEX3_MovementSystem::IsAtPos()
{
	if (!m_Owner) return true;
	const FVector _currentPos = m_Owner->GetActorLocation();
	const float _dist = FVector::Distance(_currentPos, m_PosToMove);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), _dist);
	return FVector::Distance(_currentPos, m_PosToMove) < m_MinDist;
}

void UEX3_MovementSystem::UpdateIsAtPos()
{
	//m_IsAtPos = IsAtPos(m_PosToMove);
}

void UEX3_MovementSystem::UpdateMovementSystem()
{
	if (IsAtPos()) onPosReached.Broadcast();
	else onMoveToPos.Broadcast(); 
}

void UEX3_MovementSystem::MoveToPos()
{
	if (!m_Controller)return;
	m_Controller->MoveToLocation(m_PosToMove);
	m_Path = UAIBlueprintHelperLibrary::GetCurrentPathPoints(m_Controller);
}

void UEX3_MovementSystem::RotateToPos()
{
	if (!m_Owner)return;
	const FVector _posToLook = FVector(m_PosToMove.X, m_PosToMove.Y, m_Owner->GetActorLocation().Z);
	const FRotator _lookAtRotation = UKismetMathLibrary::FindLookAtRotation(m_Owner->GetActorLocation(), _posToLook);
	const FRotator _newRotation = UKismetMathLibrary::RInterpTo_Constant(m_Owner->GetActorRotation(), _lookAtRotation, GetWorld()->TimeSeconds, m_SpeedRotate);
	m_Owner->SetActorRotation(_newRotation);
}

void UEX3_MovementSystem::GoToPos()
{
	m_MinDist = m_MaxDistApproach;
	MoveToPos();
	RotateToPos();
}

void UEX3_MovementSystem::Stop()
{
	if (m_IsInChase) m_MinDist = m_MaxDistMoveAway;
	m_Controller->StopMovement();
	RotateToPos();
}

