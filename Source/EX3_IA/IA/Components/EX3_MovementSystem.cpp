// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_MovementSystem.h"
#include "EX3_IA/IA/Pawn/EX3_IAPawn.h"
#include "EX3_Brain.h"

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
	InitComponent();
}


// Called every frame
void UEX3_MovementSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEX3_MovementSystem::InitComponent()
{
	m_Owner = Cast<AEX3_IAPawn>(GetOwner());
	if (!m_Owner)return;
	m_Brain = m_Owner->GetBrain();
}

void UEX3_MovementSystem::MoveToPos()
{
	if (!m_Owner)return;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_Owner->GetController(), m_PosToMove);
}

void UEX3_MovementSystem::RotateToPos()
{
	if (!m_Owner)return;
	const FRotator _newRotation = UKismetMathLibrary::FindLookAtRotation(m_Owner->GetActorLocation(), m_PosToMove);
	m_Owner->SetActorRotation(_newRotation);
}

