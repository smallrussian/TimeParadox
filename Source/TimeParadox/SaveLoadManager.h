#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveLoadManager.generated.h"

UCLASS()
class TIMEPARADOX_API ASaveLoadManager : public AActor
{
	GENERATED_BODY()

public:
	// Save game function
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveGameProgress(AActor* Player);

	// Load game function
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadGameProgress(AActor* Player);
};
