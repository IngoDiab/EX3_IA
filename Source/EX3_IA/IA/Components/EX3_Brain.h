// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_Brain.generated.h"

class AEX3_IAPawn;
class UEX3_FSM;
class UEX3_DetectionSystem;
class UEX3_MovementSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_Brain : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(EditAnywhere) UEX3_FSM* m_FSM = nullptr;
	UPROPERTY(EditAnywhere) UEX3_DetectionSystem* m_DetectionSystem = nullptr;
	UPROPERTY(EditAnywhere) UEX3_MovementSystem* m_MovementSystem = nullptr;

public:
	DECLARE_EVENT(UEX3_Brain, UpdateBrain)
	UpdateBrain onUpdateBrain;

public:	
	// Sets default values for this component's properties
	UEX3_Brain();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE UpdateBrain* OnUpdateBrain() { return &onUpdateBrain; };

	FORCEINLINE UEX3_FSM* GetFSM() { return m_FSM; };
	FORCEINLINE UEX3_DetectionSystem* GetDetectionSystem() { return m_DetectionSystem; };
	FORCEINLINE UEX3_MovementSystem* GetMovementSystem() { return m_MovementSystem; };

public:
	void CreateComponents();
	void InitOwner();
	void AttachComponentsToOwner();

	void InitEventsComponents();
};
