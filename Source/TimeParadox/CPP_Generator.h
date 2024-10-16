// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_InteractionInterface.h"
#include "TimeParadoxCharacter.h"
#include "CPP_Generator.generated.h"

UCLASS()
class TIMEPARADOX_API ACPP_Generator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Generator();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

private:
	// Mesh component
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> GeneratorMesh = nullptr;


};
