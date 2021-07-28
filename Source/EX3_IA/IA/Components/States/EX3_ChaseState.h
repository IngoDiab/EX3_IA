// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EX3_State.h"
#include "EX3_ChaseState.generated.h"

class UEX3_MovementSystem;

UCLASS()
class EX3_IA_API UEX3_ChaseState : public UEX3_State
{
	GENERATED_BODY()

	UPROPERTY() UEX3_MovementSystem* m_MoveSystem = nullptr;
	
public:
	void InitState(UEX3_Brain& _brain) override;
	void EnterState() override;
	UEX3_Transition* UpdateState() override;
	void ExitState() override;

public:
	void UpdateMove() const;
};
