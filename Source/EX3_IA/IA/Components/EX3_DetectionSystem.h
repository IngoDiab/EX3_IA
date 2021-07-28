// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EX3_DetectionSystem.generated.h"

class AEX3_IAPawn;
class UEX3_Brain;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EX3_IA_API UEX3_DetectionSystem : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere) AEX3_IAPawn* m_Owner = nullptr;
	UPROPERTY(VisibleAnywhere) UEX3_Brain* m_Brain = nullptr;
	UPROPERTY() USceneComponent* m_OwnerEyesLocation = nullptr;

	UPROPERTY(VisibleAnywhere) TArray<AActor*> m_ActorToIgnore;
	UPROPERTY(EditAnywhere) float m_DistanceVision = 1000;
	UPROPERTY(EditAnywhere) float m_AngleVision = 90;
	UPROPERTY(EditAnywhere) float m_ModuloVision = 0;

	UPROPERTY(VisibleAnywhere) ACharacter* m_PlayerSpotted = nullptr;
	UPROPERTY(VisibleAnywhere) bool m_IsPlayerSpotted = false;

public:
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSpottedDelegate, ACharacter*, _target);
	//FPlayerSpottedDelegate onPlayerSpottedDelegate;

	DECLARE_EVENT(UEX3_DetectionSystem, PlayerSpotted)
	PlayerSpotted onPlayerSpotted;

	DECLARE_EVENT_OneParam(UEX3_DetectionSystem, PlayerTracked, FVector)
	PlayerTracked onPlayerTracked;

	DECLARE_EVENT(UEX3_DetectionSystem, PlayerLost)
	PlayerLost onPlayerLost;

public:	
	// Sets default values for this component's properties
	UEX3_DetectionSystem();

protected:
	virtual void PostInitProperties() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//FORCEINLINE FPlayerSpottedDelegate* OnPlayerSpottedDelegate() { return &onPlayerSpottedDelegate; };
	FORCEINLINE PlayerSpotted* OnPlayerSpotted() { return &onPlayerSpotted; };
	FORCEINLINE PlayerTracked* OnPlayerTracked() { return &onPlayerTracked; };
	FORCEINLINE PlayerLost* OnPlayerLost() { return &onPlayerLost; };

	FORCEINLINE void SetIsSpotPlayer(const bool _spot) { m_IsPlayerSpotted = _spot; };

public:
	//void InitEvents();
	void InitComponent();

	void UpdateVisualDetection();
	bool VisionDetection();
	bool VisionLineTrace(const float _angle);
	//UFUNCTION() void SpotTarget(ACharacter* _target);
	void RegisterTarget(ACharacter* _target);
	void ResetTarget();
};
