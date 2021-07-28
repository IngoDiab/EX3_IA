// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_CACSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_CACSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) bool m_IsLightAttacking = false;
	UPROPERTY(VisibleAnywhere) bool m_IsHeavyAttacking = false;
	UPROPERTY(VisibleAnywhere) float m_NumberAttackInRow = 0;

public:
	DECLARE_EVENT(UEX3_CACSystem, HeavyAttackCombo)
	HeavyAttackCombo onHeavyAttackCombo;

	DECLARE_EVENT(UEX3_CACSystem, LightAttackCombo)
	LightAttackCombo onLightAttackCombo;

public:
	FORCEINLINE HeavyAttackCombo* OnHeavyAttackCombo() { return &onHeavyAttackCombo; };
	FORCEINLINE LightAttackCombo* OnLightAttackCombo() { return &onLightAttackCombo; };

public:	
	// Sets default values for this component's properties
	UEX3_CACSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void ChooseTypeAttack();
	void Attack();
		
};
