// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiate mesh component and set to root
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	RootComponent = MeshComp;
	
	OpenAngle = 90.0f;  // Set default door open angle to 90 degrees
	DoorSpeed = 2.0f;   // How fast the door opens
	bIsOpen = false;
	bOpening = false;
}


// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	// Store the initial rotation of the door
	InitialRotation = GetActorRotation();
	TargetRotation = InitialRotation;
	
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// If the door is in the process of opening or closing, interpolate its rotation
	if (bOpening)
	{
		
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, DoorSpeed);

		SetActorRotation(NewRotation);

		if (NewRotation.Equals(TargetRotation, 1.0f))
		{
			bOpening = false;  // Stop when the door reaches the target rotation
		}
	}

}


void ADoor::ToggleDoor()
{
		
	if (!bIsOpen)
	{
		
		// Set the target rotation to open the door
		TargetRotation = InitialRotation + FRotator(0.0f, OpenAngle, 0.0f);
		bOpening = true;
		bIsOpen = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Door Opened"));
	}else
	{
		// Set the target rotation to close the door
		TargetRotation = InitialRotation;
		bOpening = true;
		bIsOpen = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Door Closed"));
	}

	
}



