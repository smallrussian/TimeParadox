// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_VisionComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UCPP_VisionComponent::UCPP_VisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_VisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPP_VisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// Executes object sweep to determine if specified object type was found
AActor* UCPP_VisionComponent::LookForObjectType(FCollisionObjectQueryParams ObjectQueryParams, bool bShouldDraw, float DrawDuration)
{

	if(this)
	{
		// Start of the sweep is the location of this owner's scene component
           FVector SweepStart = GetComponentLocation();

		// Determines the end of the sweep
	   FVector SweepEnd;
	 
	   // Determine if owner has camera component
	   UCameraComponent* OwnerCam = GetOwner()->GetComponentByClass<UCameraComponent>();
	 
	   // If owner has a camera, use its forward vector to calculate end point
	   // This can be found by getting the camera's rotation and converting to a vector
	   if (OwnerCam)
	   {
	      SweepEnd = SweepStart + (OwnerCam->GetComponentRotation().Vector() * ViewDistance);
	   }
	 
	   // If owner does not have a camera, use the owner's forward vector to calculate end point
	   else
	   {
	      SweepEnd = SweepStart + (GetOwner()->GetActorForwardVector() * ViewDistance);
	   }
	 
	   // Collision query parameters to further customize sweep collision behavior
	   // The owner of this component should be ignored by the sweep
	   FCollisionQueryParams QueryParams;
	   QueryParams.AddIgnoredActor(GetOwner());
	 
	   // The shape to use in the object type sweep
	   // Initialize sphere's radius to SphereRadius property
	   FCollisionShape SweepShape;
	   SweepShape.SetSphere(SphereRadius);
	 
	   // Stores result of sweep
	   FHitResult SweepResult;
	 
	   // Execute sweep for specified object type
	   GetWorld()->SweepSingleByObjectType(SweepResult, SweepStart, SweepEnd, FQuat::Identity, ObjectQueryParams, SweepShape, QueryParams);
	   
	   // If debug sphere should be drawn, do so
	   if (bShouldDraw)
	   {
	      // Determines location debug sphere should be drawn (based on whether or not hit occurred)
	      FVector DebugPoint = SweepResult.bBlockingHit ? SweepResult.ImpactPoint : SweepEnd;
	 
	      // Determines color of debug sphere (based on whether or not hit occurred)
	      FColor DebugColor = SweepResult.bBlockingHit ? FColor::Green : FColor::Red;
	 
	      // Draw sphere
	      DrawDebugSphere(GetWorld(), DebugPoint, SphereRadius, 32.f, DebugColor, false, DrawDuration);
	   }
		
	   // If the object type was found, return the hit actor, if not, return null
	   return SweepResult.bBlockingHit ? SweepResult.GetActor() : nullptr;
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("SceneComponent is null!"));
		return nullptr;
	}
   
 
   
}

