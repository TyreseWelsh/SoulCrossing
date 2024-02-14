// Fill out your copyright notice in the Description page of Project Settings.


#include "Minion.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "MinionSoul.h"

// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Temporary static mesh to represent the player character (will be replaced with a skeletal mesh later down the line)
	PlayerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerStaticMesh->SetupAttachment(RootComponent);
	PlayerNoseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nose"));
	PlayerNoseMesh->SetupAttachment(PlayerStaticMesh);
	
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
}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMinion::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMinion::Look);

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
	// Here we will set the controller to control this or something like that and play the revive animation
	
	UE_LOG(LogTemp, Error, TEXT("POSSESSED!"));
}

void AMinion::Move(const FInputActionValue& Value)
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

void AMinion::Look(const FInputActionValue& Value)
{
	FVector LookAxisVector = Value.Get<FVector>();																// Getting the input value as a FVector which we store

	if (GetController() != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);																// Add the input values to the pawns Yaw and Pitch
		AddControllerPitchInput(LookAxisVector.Y);																//
	}
}

void AMinion::UnPossess(const FInputActionValue& Value)
{
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	AMinionSoul* playerSoul = GetWorld()->SpawnActor<AMinionSoul>(BP_Soul, GetActorTransform());
	playerSoul->SetSoulEnergy(StoredSoulEnergy);
	UE_LOG(LogTemp, Error, TEXT("Energy going back to soul: %i"), StoredSoulEnergy);
	GetController()->Possess(playerSoul);
}