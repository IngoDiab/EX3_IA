// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EX3_State.generated.h"

class UEX3_Transition;
class UEX3_Brain;
class UEX3_FSM;

UCLASS(ABSTRACT)
class EX3_IA_API UEX3_State : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TArray<UEX3_Transition*> m_Transitions;
	UPROPERTY(VisibleAnywhere) UEX3_Brain* m_Brain;
	UPROPERTY(VisibleAnywhere) UEX3_FSM* m_FSM;
	
public:
	virtual void InitState(UEX3_Brain& _brain);
	void AddTransition(UEX3_Transition& _transition);

	virtual void EnterState() PURE_VIRTUAL(UEX3_State::BeginState, );
	virtual UEX3_Transition* UpdateState();
	virtual void ExitState() PURE_VIRTUAL(UEX3_State::ExitState, );
};
