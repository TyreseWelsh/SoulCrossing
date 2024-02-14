// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlordController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AOverlordController::AOverlordController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup default object hierarchy
	// Pawn root which the camera will revolve around
	/*PlayerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempMesh"));
	PlayerBase->SetupAttachment(RootComponent);*/

	// Camera which will act as the viewport
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	if (PlayerBase != nullptr)
	{
	}
	PlayerCamera->SetupAttachment(RootComponent);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

// Called when the game starts or when spawned
void AOverlordController::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))													// Casting actor controller to a controller that is used for pawns
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))		// Accessing this players local input system so that I may alter it
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);																		// Setting this players beginning input mapping context which for most will be "Default"
		}
	}
}

// Called every frame
void AOverlordController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOverlordController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOverlordController::Move);

		EnhancedInputComponent->BindAction(UseSoulAction, ETriggerEvent::Triggered, this, &AOverlordController::UseSoul);
	}
}

void AOverlordController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetController() != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();												// Rotation of forward facing pawn
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);					// By default unreal uses X as the forward vector so we are getting that based on the pawns Yaw rotation

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);						// By default unreal uses Y as the right vector direction so we are also getting that
		//UE_LOG(LogTemplateCharacter, Error, TEXT("Speed: x: %f, y: %f"), MovementVector.X, MovementVector.Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);													// Adding input values Y value to get forward/backward movement since that is what the values translate to
		AddMovementInput(RightDirection, MovementVector.X);														// Adding input values X value to get right/left movement ^
	}
}

void AOverlordController::UseSoul(const FInputActionValue& Value)
{
	
}