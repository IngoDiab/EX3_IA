// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_CACSystem.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UEX3_CACSystem::UEX3_CACSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEX3_CACSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEX3_CACSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEX3_CACSystem::ChooseTypeAttack()
{
	const float _randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 100);
	if (_randomNumber <= m_PercentHeavyAttack)
		m_IsHeavyAttacking = true;
	else
		m_IsLightAttacking = true;
}

void UEX3_CACSystem::Attack()
{
	if (m_IsLightAttacking) onLightAttackCombo.Broadcast();
	else if (m_IsHeavyAttacking) onHeavyAttackCombo.Broadcast();
}

void UEX3_CACSystem::ResetCombo()
{
	onEndCombo.Broadcast();
}

