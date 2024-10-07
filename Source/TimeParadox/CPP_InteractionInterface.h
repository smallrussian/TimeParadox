// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TIMEPARADOX_API ICPP_InteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Interactive actors' functionality to execute when activated
	virtual void ActivateActor() = 0;
};
