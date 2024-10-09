// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_InteractionInterface.h"
#include "CPP_LightController.h"
#include "Components/PointLightComponent.h"
#include "CPP_Switch.generated.h"



UCLASS()
class TIMEPARADOX_API ACPP_Switch : public AActor, public ICPP_InteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Switch();
	
	// Switch's implementation of CPP_InteractionInterface's ActivateActor function
	virtual void ActivateActor() override;
 
	// Sets the color of the switch's button material
	void SetButtonColor();
 
	// Sets whether or not a switch can be activated
	void SetCanActivate(bool bIsActivatable) { bCanActivate = bIsActivatable; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Mesh component
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> MeshComp = nullptr;
 
	// Parent material instance to assign to switch button mesh
	UPROPERTY(EditDefaultsOnly, Category = "Switch Properties")
	TObjectPtr<class UMaterialInstance> ParentMaterial = nullptr;
 
	// Dynamic material to create from this parent
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMaterial = nullptr;
 
	// Keeps track of whether or not a switch can be activated at any time
	// EditInstanceOnly means that only instances of this class in the level can have this property set
	UPROPERTY(EditInstanceOnly, Category = "Switch Properties")
	bool bActivateAnyTime = true;
 
	// Keeps track of whether or not a switch can be activated
	UPROPERTY(VisibleAnyWhere, Category = "Switch Properties")
	bool bCanActivate = false;
 
	// Keeps track of whether or not a switch is currently active
	UPROPERTY(VisibleAnyWhere, Category = "Switch Properties")
	bool bIsActivated = false;
 
	// Keeps track of whether or not a switch has been activated
	UPROPERTY(VisibleAnyWhere, Category = "Switch Properties")
	bool bHasActivated = false;
 
	// Actor linked to a switch that should activate when the switch does
	// EditInstanceOnly means that only instances of this class in the level can have this property set
	UPROPERTY(EditInstanceOnly, Category = "Switch Properties")
	TObjectPtr<AActor> LinkedActor = nullptr;

	// Reference to the door that this button controls
	UPROPERTY(EditAnywhere, Category = "Switch Properties")
	class ADoor* DoorToControl;
	
	UPROPERTY(EditAnywhere, Category = "Switch Properties")
	class ACPP_LightController* bp_lightcontroller;

};
