// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EX3_State.h"
#include "EX3_CACState.generated.h"

class UEX3_CACSystem;

UCLASS()
class EX3_IA_API UEX3_CACState : public UEX3_State
{
	GENERATED_BODY()

	UPROPERTY() UEX3_CACSystem* m_CACSystem = nullptr;

public:
	void InitState(UEX3_Brain& _brain) override;
	void EnterState() override;
	UEX3_Transition* UpdateState() override;
	void ExitState() override;
};
