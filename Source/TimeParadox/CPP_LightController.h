#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"
#include "CPP_LightController.generated.h"

UCLASS()
class TIMEPARADOX_API ACPP_LightController : public AActor
{
    GENERATED_BODY()

public:    
    // Sets default values for this actor's properties
    ACPP_LightController();
    
    // UPROPERTY(EditDefaultsOnly, Category = "Switch Properties")
    // TObjectPtr<class UMaterialInstance> FlashRedMaterial = nullptr;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Array to hold references to multiple PointLightComponents
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
    TArray<AActor*> ControlledLights;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
    TArray<AActor*> EmergencyLights;
    
    // Function to control lights
    UFUNCTION(BlueprintCallable, Category = "LightControl")
    void ToggleLights(bool bIsOn);

    UFUNCTION(BlueprintCallable, Category = "LightControl")
    void ToggleEmergencyLightsColor(bool bIsOn);

};
