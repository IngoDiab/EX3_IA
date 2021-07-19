// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_Brain.generated.h"

class AEX3_IAPawn;
class UEX3_FSM;
class UEX3_DetectionSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_Brain : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(EditAnywhere) UEX3_FSM* m_FSM = nullptr;
	UPROPERTY(EditAnywhere) UEX3_DetectionSystem* m_DetectionSystem = nullptr;


public:	
	// Sets default values for this component's properties
	UEX3_Brain();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void CreateComponents();
	void InitOwner();
	void AttachComponentsToOwner();
};
