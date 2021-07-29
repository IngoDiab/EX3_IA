// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_MovementSystem.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;
class AAIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_MovementSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) AAIController* m_Controller = nullptr;
	UPROPERTY(VisibleAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	//UPROPERTY(VisibleAnywhere) UEX3_Brain* m_Brain = nullptr;

	UPROPERTY(VisibleAnywhere) FVector m_PosToMove = FVector(0);
	UPROPERTY(VisibleAnywhere) TArray<FVector> m_Path;
	UPROPERTY(EditAnywhere) bool m_IsInChase = false;
	//UPROPERTY(EditAnywhere) bool m_IsAtPos = false;
	UPROPERTY(EditAnywhere) float m_SpeedRotate = 1000;
	UPROPERTY(EditAnywhere) float m_MinDist = 0;
	UPROPERTY(EditAnywhere) float m_MaxDistApproach = 100;
	UPROPERTY(EditAnywhere) float m_MaxDistMoveAway = 300;

public:
	DECLARE_EVENT(UEX3_MovementSystem, MovingToPos)
	MovingToPos onMoveToPos;
	
	DECLARE_EVENT(UEX3_MovementSystem, PosReached)
	PosReached onPosReached;

public:	
	// Sets default values for this component's properties
	UEX3_MovementSystem();

protected:
	virtual void PostInitProperties() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE MovingToPos* OnMoveToPos() { return &onMoveToPos; };
	FORCEINLINE PosReached* OnPosReached() { return &onPosReached; };
	FORCEINLINE void SetPosToMove(const FVector _pos) { m_PosToMove = _pos; };
	FORCEINLINE void SetIsInChase(const bool _inChase) { m_IsInChase = _inChase; };

public:
	//void InitEvents();
	void InitComponent();
	bool IsAtPos();

	void UpdateIsAtPos();

	void UpdateMovementSystem();

	void MoveToPos();
	void RotateToPos();

	void GoToPos();
	void Stop();
		
};
