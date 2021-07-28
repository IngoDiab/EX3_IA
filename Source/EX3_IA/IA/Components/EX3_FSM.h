// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_FSM.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;

class UEX3_State;
class UEX3_Transition;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_FSM : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(VisibleAnywhere) UEX3_Brain* m_Brain = nullptr;

	UPROPERTY(VisibleAnywhere) TArray<UEX3_State*> m_States;
	UPROPERTY(VisibleAnywhere) UEX3_State* m_CurrentState;

	UPROPERTY(VisibleAnywhere) bool m_IsStarted = false;

	//TRANSITIONS BOOL
	UPROPERTY(VisibleAnywhere) bool m_UseRandomWaitingTime = true;
	UPROPERTY(VisibleAnywhere) float m_WaitingTime = 0;
	UPROPERTY(VisibleAnywhere) bool m_PlayerSeen = false;
	UPROPERTY(VisibleAnywhere) bool m_IsAtRange = false;
	UPROPERTY(VisibleAnywhere) bool m_IsWaiting = false;
	//

public:	
	// Sets default values for this component's properties
	UEX3_FSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE void StartFSM() { m_IsStarted = true; };

	//TRANSITIONS BOOL
	FORCEINLINE bool GetUseRandomWaitingTime() const { return m_UseRandomWaitingTime; };

	FORCEINLINE void SetWaitingTime(const float _waitingTime) { m_WaitingTime = _waitingTime; };
	FORCEINLINE float GetWaitingTime() const { return m_WaitingTime; };

	FORCEINLINE void SetIsPlayerSeen(const bool _seen) { m_PlayerSeen = _seen; };
	FORCEINLINE bool IsPlayerSeen() const { return m_PlayerSeen; };
	
	FORCEINLINE void SetIsAtRange(const bool _atRange) { m_IsAtRange = _atRange; };
	FORCEINLINE bool IsAtRange() const { return m_IsAtRange; };
	
	FORCEINLINE void SetIsWaiting(const bool _isWaiting) { m_IsWaiting = _isWaiting; };
	FORCEINLINE bool IsWaiting() const { return m_IsWaiting; };
	//

public:
	void InitComponent();
	void InitFSM();
	void SetStartState(UEX3_State& _state);

	void UpdateFSM();
	void SetNextState(const UEX3_Transition* _state);
};
