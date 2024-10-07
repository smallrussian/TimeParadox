// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_InteractionInterface.h"
#include "Door.generated.h"

UCLASS()
class TIMEPARADOX_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	void ToggleDoor();

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
	
	// Dynamic material to create from this parent
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMaterial = nullptr;
	
	// Keeps track of whether or not a switch is currently active
	UPROPERTY(VisibleAnyWhere, Category = "Door Properties")
	bool bIsOpen = false;

	UPROPERTY(EditAnywhere, Category = "Door Properties")
	float OpenAngle;  // How much to rotate when opening

	UPROPERTY(EditAnywhere, Category = "Door Properties")
	float DoorSpeed;  // How fast the door opens

	
	bool bOpening;

	FRotator InitialRotation;
	FRotator TargetRotation;


};
