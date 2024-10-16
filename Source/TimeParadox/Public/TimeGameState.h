// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TimeGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETimelineState : uint8
{
	Past UMETA(DisplayName = "Past"),
	Present UMETA(DisplayName = "Present"),
};

UCLASS()
class TIMEPARADOX_API ATimeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATimeGameState();

	UPROPERTY(BlueprintReadOnly, Category = "Time")
	ETimelineState CurrentTimeline;

	virtual void BeginPlay() override;
	
};
