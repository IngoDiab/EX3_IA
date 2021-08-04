#include "EX3_CACSystem.h"

#include "Kismet/KismetMathLibrary.h"

UEX3_CACSystem::UEX3_CACSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEX3_CACSystem::BeginPlay()
{
	Super::BeginPlay();

}

void UEX3_CACSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

