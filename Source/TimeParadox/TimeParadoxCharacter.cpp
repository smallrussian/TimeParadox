#include "TimeParadoxCharacter.h"
#include "TimeParadoxProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "CPP_InteractionInterface.h"
#include "CPP_VisionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATimeParadoxCharacter

ATimeParadoxCharacter::ATimeParadoxCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Instantiate vision component and attach to camera component
	VisionComp = CreateDefaultSubobject<UCPP_VisionComponent>(TEXT("Vision Component"));
	VisionComp->SetupAttachment(FirstPersonCameraComponent);

	// Initialize stopwatch variables
	StopwatchTime = 0.0f;
	bStopwatchRunning = false;
}

void ATimeParadoxCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add stopwatch widget to viewport
	if (StopwatchWidgetClass)
	{
		StopwatchWidget = CreateWidget<UUserWidget>(GetWorld(), StopwatchWidgetClass);
		if (StopwatchWidget)
		{
			StopwatchWidget->AddToViewport();
		}
	}
}

void ATimeParadoxCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update stopwatch time if running
	if (bStopwatchRunning)
	{
		UpdateStopwatch(DeltaTime);
	}
}

void ATimeParadoxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimeParadoxCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATimeParadoxCharacter::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATimeParadoxCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// Stopwatch functions
void ATimeParadoxCharacter::StartStopwatch()
{
	bStopwatchRunning = true;
}

void ATimeParadoxCharacter::StopStopwatch()
{
	bStopwatchRunning = false;
}

void ATimeParadoxCharacter::ResetStopwatch()
{
	bStopwatchRunning = false;
	StopwatchTime = 0.0f;

	// Reset the display
	if (StopwatchWidget)
	{
		UTextBlock* StopwatchText = Cast<UTextBlock>(StopwatchWidget->GetWidgetFromName("StopwatchText"));
		if (StopwatchText)
		{
			StopwatchText->SetText(FText::FromString(TEXT("00:00.00")));
		}
	}
}

void ATimeParadoxCharacter::UpdateStopwatch(float DeltaTime)
{
	StopwatchTime += DeltaTime;

	// Format the time as MM:SS.MS
	int Minutes = FMath::FloorToInt(StopwatchTime / 60.0f);
	int Seconds = FMath::FloorToInt(FMath::Fmod(StopwatchTime, 60.0f));
	int Milliseconds = FMath::FloorToInt((StopwatchTime - FMath::FloorToInt(StopwatchTime)) * 100);

	FString FormattedTime = FString::Printf(TEXT("%02d:%02d.%02d"), Minutes, Seconds, Milliseconds);

	// Update the UI
	if (StopwatchWidget)
	{
		UTextBlock* StopwatchText = Cast<UTextBlock>(StopwatchWidget->GetWidgetFromName("StopwatchText"));
		if (StopwatchText)
		{
			StopwatchText->SetText(FText::FromString(FormattedTime));
		}
	}
}

void ATimeParadoxCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATimeParadoxCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATimeParadoxCharacter::Interact(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You pressed the interact key!"));
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	AActor* HitActor = VisionComp->LookForObjectType(ObjectParams, true, 5);

	if (HitActor)
	{
		if (ICPP_InteractionInterface* ActorInterface = Cast<ICPP_InteractionInterface>(HitActor))
		{
			ActorInterface->ActivateActor();
		}
	}
}
