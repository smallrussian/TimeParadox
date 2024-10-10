#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_InteractionInterface.h"
#include "Generator.generated.h"

UCLASS(Blueprintable)  // Make the class Blueprintable so it can be extended in Blueprints
class TIMEPARADOX_API AGenerator : public AActor, public ICPP_PushInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Implement interaction interface
	virtual void ActivateActor(ATimeParadoxCharacter*) override;
	
private:
	// Static mesh component for the generator (for collision and visuals)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GeneratorMesh;

	// Boolean to track if the generator is being pushed
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsBeingPushed;

	// Reference to the player pushing the generator
	UPROPERTY()
	class ATimeParadoxCharacter* PushingPlayer;

	// Speed at which the generator is pushed
	float PushSpeed;

	// bool
	bool bPushed;
	// End pushing logic
	void StopPushing();
};
