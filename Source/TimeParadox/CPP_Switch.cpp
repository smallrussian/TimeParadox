// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Switch.h"

#include "Door.h"

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
	
	// Determine if the switch in question can be activated
	if (bCanActivate || bHasActivated || bActivateAnyTime)
	{
		
		// Flip the switch's activation status
		bIsActivated = !bIsActivated;
 
		// Change color parameter of dynamic material to reflect activation status
		SetButtonColor();

		if (DoorToControl)
		{
			DoorToControl->ToggleDoor();
		}
 
		// If the switch has not already activated, it now has
		if (!bHasActivated)
		{
			bHasActivated = true;
		}
 
		// If the switch has a linked actor ...
		if (LinkedActor)
		{
			// Attempt to get that actor's Interaction interface
			// Make sure you are declaring a pointer of type 'I' CPP_InteractionInterface, not 'U'
			if (ICPP_InteractionInterface* ActorInterface = Cast<ICPP_InteractionInterface>(LinkedActor))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Here"));
				// Execute their version of ActivateActor
				ActorInterface->ActivateActor();
			}
		}
 
		// Debug: Notify that no linked actor has been assigned to the switch
		else
		{
			// Don't forget to dereference return value of name
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch: No Linked Actor Assigned"));
			//PRINT_VAR("Switch %s: No Linked Actor Assigned", Red, *GetActorNameOrLabel());
		}
	}
 
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Button status: "+ FString::FromInt(bIsActivated)));
}

// Sets the color of the switch's button material
void ACPP_Switch::SetButtonColor()
{
	// Change color parameter of dynamic material to match activation status
	FColor ButtonColor = bIsActivated ? FColor::Green : FColor::Red;
 
	// Set button material's color parameter
	DynamicMaterial->SetVectorParameterValue("Button Color", ButtonColor);
}

