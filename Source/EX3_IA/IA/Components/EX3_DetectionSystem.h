// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_DetectionSystem.generated.h"

class AEX3_IAPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_DetectionSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY() USceneComponent* m_OwnerEyesLocation = nullptr;

	UPROPERTY(VisibleAnywhere) TArray<AActor*> m_ActorToIgnore;
	UPROPERTY(EditAnywhere) float m_DistanceVision = 1000;
	UPROPERTY(EditAnywhere) float m_AngleVision = 90;
	UPROPERTY(EditAnywhere) float m_ModuloVision = 0;

public:	
	// Sets default values for this component's properties
	UEX3_DetectionSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void InitComponent();

	bool VisionLineTrace(const float _angle);
	void VisionDetection();
};
