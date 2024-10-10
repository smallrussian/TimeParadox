#include "Generator.h"
#include "TimeParadoxCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimeParadoxPlayerController.h"
// Sets default values
AGenerator::AGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the generator's static mesh component
	GeneratorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratorMesh"));
	GeneratorMesh->SetSimulatePhysics(true); // Enable physics simulation so it can be pushed around
	RootComponent = GeneratorMesh;

	PushSpeed = 200.0f; // Default speed for pushing the generator
	bIsBeingPushed = false;
	bPushed = false;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the generator is being pushed, move it forward based on player's input
	if (bIsBeingPushed && PushingPlayer)
	{
		FVector ForwardDirection = PushingPlayer->GetActorForwardVector();
		GeneratorMesh->AddForce(ForwardDirection * PushSpeed * GeneratorMesh->GetMass());
	}
}

// Implement the interaction interface's ActivateActor function
void AGenerator::ContinuousActivateActor(ATimeParadoxCharacter player*)
{
	PushingPlayer = player;
	if (bIsBeingPushed)
	{
		// Start pushing the generator
		ATimeParadoxPlayerController* PlayerController = Cast<ATimeParadoxPlayerController>(PushingPlayer->GetController());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You PUSHED THE GENERATOR!"));

		if (PlayerController)
		{
			bIsBeingPushed = true;
			PushingPlayer = Cast<ATimeParadoxCharacter>(PlayerController->GetPawn());
		}
	}
	else
	{
		// Stop pushing the generator
		StopPushing();
	}
}

// Stop pushing the generator
void AGenerator::StopPushing()
{
	bIsBeingPushed = false;
	PushingPlayer = nullptr;
}
void ActivateActor(ATimeParadoxCharacter*){}