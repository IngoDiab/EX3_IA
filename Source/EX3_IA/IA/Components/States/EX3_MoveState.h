// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EX3_State.h"
#include "EX3_MoveState.generated.h"

/**
 * 
 */
UCLASS()
class EX3_IA_API UEX3_MoveState : public UEX3_State
{
	GENERATED_BODY()
	
public:
	void EnterState() const override;
	UEX3_Transition* UpdateState() const override;
	void ExitState() const override;
};
