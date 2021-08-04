// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_FSM.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;

class UEX3_State;
class UEX3_IDLEState;
class UEX3_ChaseState;
class UEX3_WaitState;
class UEX3_CACState;

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

	UPROPERTY(EditAnywhere) float m_MaxDistChase = 100;
	UPROPERTY(EditAnywhere) float m_MaxDistCombat = 300;

	UPROPERTY(EditAnywhere) float m_MinWaitingTime = 0.1f;
	UPROPERTY(EditAnywhere) float m_MaxWaitingTime = 2;

	//TRANSITIONS BOOL
	UPROPERTY(VisibleAnywhere) bool m_UseRandomWaitingTime = true;

	UPROPERTY(VisibleAnywhere) bool m_PlayerSeen = false;
	UPROPERTY(VisibleAnywhere) bool m_IsAtPos = false;
	UPROPERTY(VisibleAnywhere) bool m_IsWaiting = false;
	UPROPERTY(VisibleAnywhere) bool m_IsAttacking = false;
	//

public:	
	UEX3_FSM();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE void StartFSM() { m_IsStarted = true; };

	FORCEINLINE float GetMaxDistChase() const { return m_MaxDistChase; };
	FORCEINLINE float GetMaxDistCombat() const { return m_MaxDistCombat; };

	FORCEINLINE float GetMinWaitingTime() const { return m_MinWaitingTime; };
	FORCEINLINE float GetMaxWaitingTime() const { return m_MaxWaitingTime; };

	//TRANSITIONS BOOL
	FORCEINLINE bool GetUseRandomWaitingTime() const { return m_UseRandomWaitingTime; };



	FORCEINLINE void SetIsPlayerSeen(const bool _seen) { m_PlayerSeen = _seen; };
	FORCEINLINE bool IsPlayerSeen() const { return m_PlayerSeen; };
	
	FORCEINLINE void SetIsAtPos(const bool _atPos) { m_IsAtPos = _atPos; };
	FORCEINLINE bool IsAtPos() const { return m_IsAtPos; };
	
	FORCEINLINE void SetIsWaiting(const bool _isWaiting) { m_IsWaiting = _isWaiting; };
	FORCEINLINE bool IsWaiting() const { return m_IsWaiting; };
	
	FORCEINLINE void SetIsAttacking(const bool _isAttacking) { m_IsAttacking = _isAttacking; };
	FORCEINLINE bool IsAttacking() const { return m_IsAttacking; };
	//

public:
	void InitComponent();

	void InitFSM();
	UEX3_State* CreateStates();
	void InitTransitionsFromIDLEState(UEX3_IDLEState& _idleState, UEX3_ChaseState& _chaseState);
	void InitTransitionsFromChaseState(UEX3_ChaseState& _chaseState, UEX3_IDLEState& _idleState, UEX3_WaitState& _waitState);
	void InitTransitionsFromWaitState(UEX3_WaitState& _waitState, UEX3_ChaseState& _chaseState, UEX3_CACState& _CACState);
	void InitTransitionsFromCACState(UEX3_CACState& _CACState, UEX3_WaitState& _waitState, UEX3_ChaseState& _chaseState);

	void SetStartState(UEX3_State& _state);

	void UpdateFSM();
	void SetNextState(const UEX3_Transition* _state);
};
