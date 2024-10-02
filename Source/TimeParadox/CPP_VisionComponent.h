// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CPP_VisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMEPARADOX_API UCPP_VisionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_VisionComponent();

	// Executes object sweep to determine if actor of specified object type was found, and if it was, returns that actor (if not returns null pointer)
	AActor* LookForObjectType(FCollisionObjectQueryParams ObjectQueryParams, bool bShouldDraw = true, float DrawDuration = 5.f);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Determines distance of queries
	// If you want to provide an initial value, I recommend something around 1500
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 500.f, ClampMax = 3000.f), Category = "Query Properties")
	float ViewDistance;
 
	// Determines radius of sphere to use in object type sweep
	// If you want to provide an initial value, I recommend something around 30
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 5.f, ClampMax = 50.f), Category = "Query Properties")
	float SphereRadius;
};
