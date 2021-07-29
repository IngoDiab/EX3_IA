// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EX3_Transition.h"
#include "EX3_CAC_To_Chase.generated.h"

/**
 * 
 */
UCLASS()
class EX3_IA_API UEX3_CAC_To_Chase : public UEX3_Transition
{
	GENERATED_BODY()
	
public:
	void EnterTransition() const override;
	void ExitTransition() const override;

	bool CheckCondition() const override;
};
