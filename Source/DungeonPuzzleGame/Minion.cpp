// Fill out your copyright notice in the Description page of Project Settings.


#include "Minion.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "MinionSoul.h"
#include "Interactable.h"


// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Speed of rotation around Yaw
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1200.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 2.f;
	
	// Camera boom to pull/push camera away from character when it collides with a world object
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera which will act as the viewport
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	PossessionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("PossessionRadius"));
	PossessionRadius->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))													// Casting actor controller to a controller that is used for pawns
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))		// Accessing this players local input system so that I may alter it
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);																		// Setting this players beginning input mapping context which for most will be "Default"
		}

	}

	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &AMinion::MontageBeginBlendOut);
}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinion::Jump()
{
	if(bCanInput)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void AMinion::MontageBeginBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == PossessionMontage)
	{
		bCanInput = true;
		Possessed = true;
	}
}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMinion::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMinion::Look);

		JumpActionBinding = &EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMinion::Interact);
		EnhancedInputComponent->BindAction(UnPossessAction, ETriggerEvent::Triggered, this, &AMinion::UnPossess);
	}
}

int AMinion::GetSoulCost_Implementation()
{
	return SoulCost;
}

void AMinion::StoreSoulEnergy_Implementation(int EnergyToStore)
{
	StoredSoulEnergy = EnergyToStore;
	UE_LOG(LogTemp, Error, TEXT("StoredEnergy: %i, PlayerEnergy: %i"), StoredSoulEnergy, EnergyToStore);
}

void AMinion::PossessThis_Implementation()
{
	bCanInput = false;
	PlayAnimMontage(PossessionMontage);
}

void AMinion::Move(const FInputActionValue& Value)
{
	if (bCanInput)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (GetController() != nullptr)
		{
			const FRotator Rotation = Controller->GetControlRotation();												// Rotation of forward facing pawn
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);					// By default unreal uses X as the forward vector so we are getting that based on the pawns Yaw rotation

			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);						// By default unreal uses Y as the right vector direction so we are also getting that

			AddMovementInput(ForwardDirection, MovementVector.Y);													// Adding input values Y value to get forward/backward movement since that is what the values translate to
			AddMovementInput(RightDirection, MovementVector.X);														// Adding input values X value to get right/left movement ^
		}
	}
}

void AMinion::Look(const FInputActionValue& Value)
{
	FVector LookAxisVector = Value.Get<FVector>();																// Getting the input value as a FVector which we store

	if (GetController() != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);																// Add the input values to the pawns Yaw and Pitch
		AddControllerPitchInput(LookAxisVector.Y);																//
	}
}

void AMinion::Interact(const FInputActionValue& Value)
{
	FHitResult hit;

	FVector TraceStartPos(GetMesh()->GetComponentLocation().X, GetMesh()->GetComponentLocation().Y, GetActorLocation().Z);			// Using actor location.z due to mesh relative offset being -110 offsetting from the actual world location
	float TraceEndXOffset = GetMesh()->GetRightVector().X * 300.f;																	// Using meshes right vector because it is actually its forward vector (Y)
	float TraceEndYOffset = GetMesh()->GetRightVector().Y * 300.f;
	FVector TraceEndPos(TraceStartPos + FVector(TraceEndXOffset, TraceEndYOffset, 0));

	GetWorld()->LineTraceSingleByChannel(hit, TraceStartPos, TraceEndPos, ECollisionChannel::ECC_Visibility);
	UE_LOG(LogTemp, Error, TEXT("SHOULD INTERACT"));
	if (hit.GetActor() != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HIT SOMETHING"));
	}
	if (IInteractable* InteractInterface = Cast<IInteractable>(hit.GetActor()))														// Checking if hit actor has interactable interface, will return true if not null
	{
		UE_LOG(LogTemp, Error, TEXT("INTERACTING"));
		InteractInterface->Execute_Interact(hit.GetActor(), this);
	}
}

void AMinion::UnPossess(const FInputActionValue& Value)
{
	if (bCanInput && GetCharacterMovement()->Velocity.Z == 0)
	{
		Possessed = false;
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);

		AMinionSoul* playerSoul = GetWorld()->SpawnActor<AMinionSoul>(BP_Soul, GetActorTransform());
		if (playerSoul != nullptr)
		{
			playerSoul->SetSoulEnergy(StoredSoulEnergy);
			GetController()->Possess(playerSoul);
		}
	}
}