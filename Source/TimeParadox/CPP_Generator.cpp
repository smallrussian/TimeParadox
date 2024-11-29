// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Generator.h"

// Sets default values
ACPP_Generator::ACPP_Generator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Instantiate mesh component and set to root
	GeneratorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Switch Mesh");
	GeneratorMesh->SetSimulatePhysics(true); // Enable physics simulation so it can be pushed around
	RootComponent = GeneratorMesh;

	
}



// Called when the game starts or when spawned
void ACPP_Generator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Generator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



