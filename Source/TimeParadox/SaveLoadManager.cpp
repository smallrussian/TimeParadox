#include "SaveLoadManager.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameSave.h"
#include "GameFramework/Actor.h"

void ASaveLoadManager::SaveGameProgress(AActor* Player)
{
    // Create a save game object
    UMyGameSave* SaveGameInstance = Cast<UMyGameSave>(UGameplayStatics::CreateSaveGameObject(UMyGameSave::StaticClass()));

    if (SaveGameInstance && Player)
    {
        // Save current level name
        SaveGameInstance->CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

        // Save player location
        SaveGameInstance->PlayerLocation = Player->GetActorLocation();

        // Example: Save player health (replace this with your actual health variable)
        SaveGameInstance->PlayerHealth = 100.0f; // Replace with actual health variable

        // Save to slot
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);

        UE_LOG(LogTemp, Log, TEXT("Game saved successfully!"));
    }
}

void ASaveLoadManager::LoadGameProgress(AActor* Player)
{
    if (UMyGameSave* LoadedGame = Cast<UMyGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0)))
    {
        if (Player)
        {
            // Load player location
            Player->SetActorLocation(LoadedGame->PlayerLocation);

            // Example: Load player health (replace this with your actual health variable)
            float LoadedHealth = LoadedGame->PlayerHealth;
            UE_LOG(LogTemp, Log, TEXT("Player health loaded: %f"), LoadedHealth);

            // Optionally, load the level if it's different
            FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
            if (LoadedGame->CurrentLevelName != CurrentLevel)
            {
                UGameplayStatics::OpenLevel(this, FName(*LoadedGame->CurrentLevelName));
            }

            UE_LOG(LogTemp, Log, TEXT("Game loaded successfully!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save game found!"));
    }
}
