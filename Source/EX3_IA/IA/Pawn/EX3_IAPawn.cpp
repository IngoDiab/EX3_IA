// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_IAPawn.h"
#include "EX3_IA/IA/Components/EX3_FSM.h"
#include "EX3_IA/IA/Components/EX3_DetectionSystem.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AEX3_IAPawn::AEX3_IAPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreateComponents();
}

// Called when the game starts or when spawned
void AEX3_IAPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEX3_IAPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEX3_IAPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEX3_IAPawn::CreateComponents()
{
	//Create Capsule Root
	m_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CreateComponentsRelativeToCapsule();
	//Create FSM
	m_FSM = CreateDefaultSubobject<UEX3_FSM>(TEXT("FSM"));
	AddOwnedComponent(m_FSM);
	//Create Detection System
	m_DetectionSystem = CreateDefaultSubobject<UEX3_DetectionSystem>(TEXT("DetectionSystem"));
	AddOwnedComponent(m_DetectionSystem);
	//Create PawnMovement
	m_PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	AddOwnedComponent(m_PawnMovement);
}

void AEX3_IAPawn::CreateComponentsRelativeToCapsule()
{
	if (!m_CapsuleComponent)return;
	RootComponent = m_CapsuleComponent;
	//Create Arrow
	m_ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	m_ArrowComponent->AttachToComponent(m_CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//Create Mesh
	m_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_Mesh->AttachToComponent(m_CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CreateComponentsRelativeToMesh();
}

void AEX3_IAPawn::CreateComponentsRelativeToMesh()
{
	if (!m_Mesh)return;
	//Create EyesLocation
	m_EyesLocation = CreateDefaultSubobject<USceneComponent>(TEXT("EyesLocation"));
	m_EyesLocation->AttachToComponent(m_Mesh, FAttachmentTransformRules::KeepRelativeTransform);
}

