// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Switch.h"

#include "Door.h"
#include "TimeGameState.h"
#include "CPP_LightController.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

// Sets default values
ACPP_Switch::ACPP_Switch()
{
	PrimaryActorTick.bCanEverTick = false;
 
	// Instantiate mesh component and set to root
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Switch Mesh");
	RootComponent = MeshComp;
 
	// Specify that this mesh is an interactive object type (should be GameTraceChannel2)
	MeshComp->SetCollisionObjectType(ECC_GameTraceChannel2);

}

// Called when the game starts or when spawned
void ACPP_Switch::BeginPlay()
{
	Super::BeginPlay();

	// If the parent material was assigned...
	if (ParentMaterial)
	{
		// Create the dynamic material from it
		DynamicMaterial = MeshComp->CreateDynamicMaterialInstance(1, ParentMaterial);
 
		// Make sure the button color is set correctly when game begins
		SetButtonColor();
	}
	// Debug: Notify that parent material was not assigned
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Parent Material Not Assigned in Switch Blueprint"));//PRINT_COLOR("Parent Material Not Assigned in Switch Blueprint", Red);
	}
	
}

// Called every frame
void ACPP_Switch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Switch's implementation of CPP_InteractionInterface's ActivateActor function
void ACPP_Switch::ActivateActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Button clicked."));

	// Get the current Game State
	ATimeGameState* GameState = GetWorld()->GetGameState<ATimeGameState>();

	if (GameState)
	{
		// Check the current timeline
		if (GameState->CurrentTimeline == ETimelineState::Present)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch is disabled in the present timeline."));
			return; // Do nothing if in the present
		}
		else if (GameState->CurrentTimeline == ETimelineState::Past)
		{
			// Toggle the activation state
			bIsActivated = !bIsActivated;

			// Change button color
			SetButtonColor();

			// Control the linked light controllers in both past and present
			for (ACPP_LightController* LightController : LightControllersToControl)
			{
				if (LightController)
				{
					LightController->ToggleLights(bIsActivated);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Lights toggled in past and present timelines."));
				}
			}

			if (DoorToControl)
			{
				DoorToControl->ToggleDoor();
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameState is null."));
	}
          
                
		    
}


// Sets the color of the switch's button material
void ACPP_Switch::SetButtonColor()
{
	// Change color parameter of dynamic material to match activation status
	FColor ButtonColor = bIsActivated ? FColor::Green : FColor::Red;
 
	// Set button material's color parameter
	DynamicMaterial->SetVectorParameterValue("Button Color", ButtonColor);
}

