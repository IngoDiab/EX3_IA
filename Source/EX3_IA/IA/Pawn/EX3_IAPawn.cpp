// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_IAPawn.h"

#include "EX3_IA/IA/Components/EX3_Brain.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEX3_IAPawn::AEX3_IAPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreateBrain();
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
	Gravity();
	RootMotion();
}

// Called to bind functionality to input
void AEX3_IAPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEX3_IAPawn::CreateBrain()
{
	m_Brain = CreateDefaultSubobject<UEX3_Brain>(TEXT("Brain"));
	AddOwnedComponent(m_Brain);
}

void AEX3_IAPawn::CreateComponents()
{
	//Create Capsule Root
	m_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CreateComponentsRelativeToCapsule();
	///
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

void AEX3_IAPawn::Gravity()
{
	if (!m_PawnMovement)return;
	const FVector _currentVelocity = m_PawnMovement->Velocity;
	const FVector _newVelocity = FVector(_currentVelocity.X, _currentVelocity.Y, _currentVelocity.Z - 98.1f);
	m_PawnMovement->Velocity = _newVelocity;
}

void AEX3_IAPawn::RootMotion()
{
	if (!m_Mesh)return;
	FRootMotionMovementParams _Params = m_Mesh->GetAnimInstance()->ConsumeExtractedRootMotion(1.0f);
	if (!_Params.bHasRootMotion)
	{
		needRotateRM = true;
		return;
	}
	FTransform _newTransform = _Params.GetRootMotionTransform();

	FTransform _test = FTransform();
	_test.SetRotation(_newTransform.GetRotation() + FRotator(0, -90 * needRotateRM, 0).Quaternion());
	needRotateRM = false;
	_newTransform.GetLocation().Normalize();
	FVector _testPos = _newTransform.GetLocation().RotateAngleAxis(-90, GetActorUpVector());
	_test.SetLocation(_testPos);
	_test.SetScale3D(GetActorScale3D());

	AddActorLocalTransform(_test, true);
}

