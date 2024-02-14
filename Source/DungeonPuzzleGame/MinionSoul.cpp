// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionSoul.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Possessable.h"


// Sets default values
AMinionSoul::AMinionSoul()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	//GetCharacterMovement()->GravityScale = 0;																				// Will instead have invisible platforms that only the soul can collide with to cross gaps

	// Temporary static mesh to represent the player character (will be replaced with a skeletal mesh later down the line)
	PlayerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerStaticMesh->SetupAttachment(RootComponent);

	// Camera boom to pull/push camera away from character when it collides with a world object
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera which will act as the viewport
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMinionSoul::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))													// Casting actor controller to a controller that is used for pawns
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))		// Accessing this players local input system so that I may alter it
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);																		// Setting this players beginning input mapping context which for most will be "Default"
		}
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMinionSoul::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMinionSoul::EndOverlap);
}

// Called every frame
void AMinionSoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionSoul::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IPossessable* PossessableInterface = Cast<IPossessable>(OtherActor))
	{
		PawnsCanPossess.AddUnique(Cast<APawn>(OtherActor));
		PawnToPossess = PawnsCanPossess[0];
	}
}

void AMinionSoul::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPossessable* PossessableInterface = Cast<IPossessable>(OtherActor))
	{

		PawnsCanPossess.Remove(Cast<APawn>(OtherActor));

		if (PawnsCanPossess.Num() > 0)
		{
			PawnToPossess = PawnsCanPossess[0];
		}
		else
		{
			PawnToPossess = nullptr;
		}
	}
}


// Called to bind functionality to input
void AMinionSoul::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMinionSoul::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMinionSoul::Look);

		EnhancedInputComponent->BindAction(PossessAction, ETriggerEvent::Triggered, this, &AMinionSoul::PossessPawn);
	}
}

void AMinionSoul::Move(const FInputActionValue& Value)
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


		// Finds the rotator from the player meshes current relative rotation to that of the movement vector
		// Then sets the relative rotation to the value of the lerp between the current mesh rotation and the target rotation
		//FVector MovementVector3D(MovementVector.Y, MovementVector.X, 0);
		//FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(PlayerStaticMesh->GetRelativeLocation(), PlayerStaticMesh->GetRelativeLocation() + MovementVector3D);

		//PlayerStaticMesh->SetRelativeRotation(UKismetMathLibrary::RInterpTo(PlayerStaticMesh->GetRelativeRotation(), LookRotation, GetWorld()->GetDeltaSeconds(), 8));
	}
}

void AMinionSoul::Look(const FInputActionValue& Value)
{
	FVector LookAxisVector = Value.Get<FVector>();																// Getting the input value as a FVector which we store

	if (GetController() != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);																// Add the input values to the pawns Yaw and Pitch
		AddControllerPitchInput(LookAxisVector.Y);																//
	}
}

void AMinionSoul::PossessPawn(const FInputActionValue& Value)
{
	// If within the collision bounds of a possessable body, call their possess function
	if (PawnToPossess != nullptr)
	{
		if (IPossessable* PossessableInterface = Cast<IPossessable>(PawnToPossess))
		{
			if (PossessableInterface->Execute_GetSoulCost(PawnToPossess) <= SoulEnergy)			// Checking if the player has enough soul energy to possess the possessable object
			{
				PossessableInterface->Execute_StoreSoulEnergy(PawnToPossess, SoulEnergy);
				PossessableInterface->Execute_PossessThis(PawnToPossess);
				GetController()->Possess(Cast<APawn>(PawnToPossess));
				Destroy();
			}
		}
	}
}