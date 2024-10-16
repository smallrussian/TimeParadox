// Fill out your copyright notice in the Description page of Project Settings.



#include "TimeGameState.h"

ATimeGameState::ATimeGameState()
{
	CurrentTimeline = ETimelineState::Present;
}

void ATimeGameState::BeginPlay()
{
	Super::BeginPlay();
}
