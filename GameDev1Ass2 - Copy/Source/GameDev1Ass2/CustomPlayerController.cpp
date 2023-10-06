// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

void ACustomPlayerController::BeginPlay() {
	Super::BeginPlay();

	//Obtains Player character and a reference to ACourseGameModeBase.
	CourseGameModeRef = Cast<ACourseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RecastTimer, this, &ACustomPlayerController::RecastPlayer, RecastDuration, false);

	if (HasAuthority()) {
		NetUpdateFrequency = 10;
		SetReplicates(true);
	}
}

void ACustomPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis(TEXT("ForwardMovement"), this, &ACustomPlayerController::MoveForwards);
	InputComponent->BindAxis(TEXT("SidewaysMovement"), this, &ACustomPlayerController::Strafe);
	InputComponent->BindAxis(TEXT("VerticalCamera"), this, &ACustomPlayerController::Turn);
	InputComponent->BindAxis(TEXT("HorizontalCamera"), this, &ACustomPlayerController::Pitch);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACustomPlayerController::JumpCharacter);
	InputComponent->BindAction(TEXT("Push"), IE_Pressed, this, &ACustomPlayerController::PushCharacter);
	InputComponent->BindAction(TEXT("Dive"), IE_Pressed, this, &ACustomPlayerController::DiveCharacter);
}

// Called every frame
void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerCharacter) {  //Checks if player has fallen off map, and if so resets them.
		if (PlayerCharacter->GetActorLocation().Z < ResetPositionPlaneLocation) ServerRestartLastCheckpoint();
	}
}

void ACustomPlayerController::JumpCharacter()
{
	if (PlayerCharacter) PlayerCharacter->Jump();
}

void ACustomPlayerController::DiveCharacter()
{
	ServerDiveCharacter();
}

void ACustomPlayerController::ServerDiveCharacter_Implementation() //Launches player direction they're facing
{
	if (PlayerCharacter) PlayerCharacter->LaunchCharacter(PlayerCharacter->GetActorForwardVector() * diveAmount, false, false);
}

bool ACustomPlayerController::ServerDiveCharacter_Validate()
{
	return true;
}

void ACustomPlayerController::ServerRestartLastCheckpoint_Implementation() //Teleports player to checkpoint location
{
	if (PlayerCharacter) PlayerCharacter->TeleportTo(CurrentSpawnLocation, FRotator{ 0.0f,0.0f,0.0f }, false, false);
}

bool ACustomPlayerController::ServerRestartLastCheckpoint_Validate()
{
	return true;
}

void ACustomPlayerController::PushCharacter()
{
	//if (PlayerCharacter) PlayerCharacter->LaunchCharacter(PlayerCharacter->GetActorForwardVector(), false, false);
}

void ACustomPlayerController::MoveForwards(float axisAmount)
{
	if (PlayerCharacter) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Strafe(float axisAmount)
{
	if (PlayerCharacter) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Turn(float axisAmount)
{
	if (PlayerCharacter) PlayerCharacter->AddControllerPitchInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Pitch(float axisAmount)
{
	if (PlayerCharacter) PlayerCharacter->AddControllerYawInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

float ACustomPlayerController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	playerHealth -= DamageAmount;

	//Tells GameMode to begin Respawn timer while dropping any Ball held and finally destroying Player Character.
	if (playerHealth <= 0) {
		PlayerCharacter->Destroy();
	}
	return DamageAmount;
}

void ACustomPlayerController::RecastPlayer()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if(PlayerCharacter) CurrentSpawnLocation = PlayerCharacter->GetActorLocation();
	else GetWorld()->GetTimerManager().SetTimer(RecastTimer, this, &ACustomPlayerController::RecastPlayer, RecastDuration, false);
}

int ACustomPlayerController::GetCurrentCheckpoint() //Used to check if visited checkpoint is progress.
{
	return CurrentCheckpoint;
}

void ACustomPlayerController::ServerSetSpawnLocation_Implementation(FVector newSpawnLocation, int Checkpoint) //Sets new checkpoint location
{
	CurrentSpawnLocation = newSpawnLocation;
	CurrentCheckpoint = Checkpoint;
}

bool ACustomPlayerController::ServerSetSpawnLocation_Validate(FVector newSpawnLocation, int Checkpoint)
{
	return true;
}

void ACustomPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, playerHealthMax, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, playerHealth, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, moveSpeed, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, rotationSpeed, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, diveAmount, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, RecastDuration, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACustomPlayerController, CurrentSpawnLocation, COND_SimulatedOnly);

}