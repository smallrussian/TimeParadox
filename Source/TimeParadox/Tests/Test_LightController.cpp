#include <iostream>

#include "../CPP_LightController.h"
#include "Engine/PointLight.h"
#include "Misc/AutomationTest.h"
#include "Engine/World.h"
#include "Components/PointLightComponent.h"
#include "FWorldFixture.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test_LightController, "TimeParadox.TimeParadox.Test_LightController",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

TUniquePtr<FWorldFixture> WorldFixture;
//test toggling lights
bool Test_LightController::RunTest(const FString& Parameters)
{
	
	std::cout<<"Here";
	// Create the world
	WorldFixture = MakeUnique<FWorldFixture>();
 
	if (TestNotNull("World", WorldFixture->GetWorld()))
	{
		
	
		UWorld* World = WorldFixture->GetWorld();
		if (!World)
		{
			AddError(TEXT("Failed to get the World context."));
			return false;
		}
		
		// Step 2: Define spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = nullptr;  // No owner needed for the test

		// Step 3: Set spawn location and rotation
		FVector SpawnLocation(0.0f, 0.0f, 300.0f);
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
		
		ACPP_LightController* lightController = World->SpawnActor<ACPP_LightController>(ACPP_LightController::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
		// Step 4: Spawn the PointLight actor
		APointLight* PointLight = World->SpawnActor<APointLight>(APointLight::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	    
		if (!PointLight)
		{
			AddError(TEXT("Failed to spawn APointLight."));
			return false;
		}

		//add the light to the light controller.
		 lightController->ControlledLights.Push(PointLight);

		//turn the lights off
		lightController->ToggleLights(false);


		for (AActor* Light : lightController->ControlledLights)
		{
			UPointLightComponent* PointLightComponent = Light->FindComponentByClass<UPointLightComponent>();
			//check to see if the point light is visible
			if(PointLightComponent->IsVisible() == true)
			{
				AddError(TEXT("Point light is visible."));
				return false;
			}
			
		}
		
	}
	// Make the test pass by returning true, or fail by returning false.
	return true;
}
