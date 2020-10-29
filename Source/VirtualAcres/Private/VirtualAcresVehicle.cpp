// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualAcresVehicle.h"
#include "VirtualAcresVehicleMovementComp.h"

// Sets default values
AVirtualAcresVehicle::AVirtualAcresVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	vehicleSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VehicleSkeletalMesh"));
	vehicleSkeletalMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	//Create box collision for determing when player is close to the item
	interactionCollisionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollisionArea"));
	interactionCollisionArea->AttachToComponent(vehicleSkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);

	MovementComponent = CreateDefaultSubobject<UVirtualAcresVehicleMovementComp>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = GetRootComponent();
}

// Called when the game starts or when spawned
void AVirtualAcresVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVirtualAcresVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVirtualAcresVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AVirtualAcresVehicle::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVirtualAcresVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVirtualAcresVehicle::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AVirtualAcresVehicle::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AVirtualAcresVehicle::LookUpAtRate);
}


void AVirtualAcresVehicle::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AVirtualAcresVehicle::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AVirtualAcresVehicle::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AVirtualAcresVehicle::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AVirtualAcresVehicle::Interact()
{
	
}

UPawnMovementComponent* AVirtualAcresVehicle::GetMovementComponent() const
{
	return MovementComponent;
}

