#include "CPP_LightController.h"

#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Engine/PointLight.h"
// Sets default values
ACPP_LightController::ACPP_LightController()
{
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACPP_LightController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACPP_LightController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to toggle lights on or off
void ACPP_LightController::ToggleLights(bool bIsOn)
{   
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Lights Should be toggling: "+FString::FromInt(bIsOn)));
     for (AActor* Light : ControlledLights)
     {
         try
         {
             URectLightComponent* RectLight = Light->FindComponentByClass<URectLightComponent>();

             if (RectLight)
                {
                    
                    RectLight->SetVisibility(bIsOn);
                 
                 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Light toggled"));
                    
                }
             continue;
         }catch (const char* e)
         {
             GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error converting to light: "+Light->GetActorNameOrLabel()+ e));

         }
         
         try
         {
             UPointLightComponent* PointLight = Light->FindComponentByClass<UPointLightComponent>();

             if (PointLight)
             {
                 
                 PointLight->SetVisibility(bIsOn);
                 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Light toggled"));
                    
             }
         }catch (const char* e)
         {
             GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error converting to light: "+Light->GetActorNameOrLabel()+ e));

         }
    }
}


void ACPP_LightController::ToggleEmergencyLightsColor(bool bIsOn)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Emergency Lights Should be toggling: "+FString::FromInt(bIsOn)));
    FLinearColor lightColor;
    if(bIsOn)
    {
        lightColor = FLinearColor::Red;        
    }else
    {
        lightColor = FLinearColor::White;
    }
    
    for (AActor* Light : EmergencyLights)
    {
        try
        {
            URectLightComponent* RectLight = Light->FindComponentByClass<URectLightComponent>();

            if (RectLight)
            {
                    
                RectLight->SetLightColor(lightColor);
                 
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("emergency Light toggled"));
                    
            }
            
        }catch (const char* e)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error converting to light: "+Light->GetActorNameOrLabel()+ e));

        }
         
        try
        {
            UPointLightComponent* PointLight = Light->FindComponentByClass<UPointLightComponent>();
            
            if (PointLight)
            {
                 
                PointLight->SetLightColor(lightColor);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("emergency Light toggled"));
                    
            }
        }catch (const char* e)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error converting to light: "+Light->GetActorNameOrLabel()+ e));

        }
    }
}

