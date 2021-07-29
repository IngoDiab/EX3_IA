// Fill out your copyright notice in the Description page of Project Settings.


#include "EX3_IAAnimation.h"

void UEX3_IAAnimation::EndCombo()
{
    onEndCombo.Broadcast();
}
