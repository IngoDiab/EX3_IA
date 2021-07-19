// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EX3_IAPawn.generated.h"

class UEX3_Brain;

class UCapsuleComponent;
class UArrowComponent;
class UFloatingPawnMovement;

UCLASS()
class EX3_IA_API AEX3_IAPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) UEX3_Brain* m_Brain = nullptr;
	UPROPERTY(EditAnywhere) USceneComponent* m_EyesLocation = nullptr;

	UPROPERTY(EditAnywhere) UCapsuleComponent* m_CapsuleComponent = nullptr;
	UPROPERTY(EditAnywhere) UArrowComponent* m_ArrowComponent = nullptr;
	UPROPERTY(EditAnywhere) USkeletalMeshComponent* m_Mesh = nullptr;
	UPROPERTY(EditAnywhere) UFloatingPawnMovement* m_PawnMovement = nullptr;

public:
	// Sets default values for this pawn's properties
	AEX3_IAPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE USceneComponent* GetEyesLocation() const { return m_EyesLocation; };

public:
	void CreateBrain();
	void CreateComponents();
	void CreateComponentsRelativeToCapsule();
	void CreateComponentsRelativeToMesh();
};
