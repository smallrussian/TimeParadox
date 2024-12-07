#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyGameSave.generated.h"

/**
 * Save game class to store player progress and game state.
 */
UCLASS()
class TIMEPARADOX_API UMyGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	// Name of the level the player is currently on
	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	FString CurrentLevelName;

	// Player's location in the world
	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	FVector PlayerLocation;

	// Player's health
	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	float PlayerHealth;

	// Add more variables as needed to store other game data
};
