// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_FSM.h"

// Sets default values for this component's properties
UEX3_FSM::UEX3_FSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEX3_FSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEX3_FSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

