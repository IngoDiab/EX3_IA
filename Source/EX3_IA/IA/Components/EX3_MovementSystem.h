// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_MovementSystem.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_MovementSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(VisibleAnywhere) UEX3_Brain* m_Brain = nullptr;

	UPROPERTY(VisibleAnywhere) FVector m_PosToMove = FVector(0);

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

public:
	void InitEvents();
	void InitComponent();
	void MoveToPos();
	void RotateToPos();
		
};
