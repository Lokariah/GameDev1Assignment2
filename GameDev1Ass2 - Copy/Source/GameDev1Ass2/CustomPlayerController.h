// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "CourseGameModeBase.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS2_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();
	UFUNCTION()
		void MoveForwards(float axisAmount);
	UFUNCTION()
		void Strafe(float axisAmount);
	UFUNCTION()
		void Turn(float axisAmount);
	UFUNCTION()
		void Pitch(float axisAmount);
	UFUNCTION()
		void JumpCharacter();
	UFUNCTION()
		void DiveCharacter();	//Launches player direction they're facing
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDiveCharacter();
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRestartLastCheckpoint(); //Teleports player to checkpoint location
	UFUNCTION()
		void PushCharacter(); //Unimplemented
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetSpawnLocation(FVector newSpawnLocation, int Checkpoint); //Sets new checkpoint location
	UFUNCTION()
		int GetCurrentCheckpoint(); //Used to check if visited checkpoint is progress.

	UPROPERTY()
		APlayerCharacter* PlayerCharacter;		  //Reference to Player's Character to control, move around and delete.

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	//Tells GameMode to begin Respawn timer while dropping any Ball held and finally destroying Player Character.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void RecastPlayer();							   //Ensures player controller is controlling player character

	UPROPERTY(EditAnywhere, Replicated)
		float playerHealthMax = 100.0f;					   //Adjustable health that PlayerHealth will adjust to.
	UPROPERTY(Replicated)
		float playerHealth = 100.0f;					   //Monitors health to see when to trigger PlayerDeath.

	UPROPERTY(EditAnywhere, Replicated)
		float moveSpeed = 100.0f;						   //Adjustable multiplier for speed.
	UPROPERTY(EditAnywhere, Replicated)
		float rotationSpeed = 200.0f;					   //Adjustable multiplier for speed.
	UPROPERTY(EditAnywhere, Replicated)
		float diveAmount = 1000.0f;						   //Adjustable amount of force added on dive.

	UPROPERTY()
		FTimerHandle RecastTimer;						   //Handle to access timer for recast if issues occur.
	UPROPERTY(EditAnywhere, Replicated)
		float RecastDuration = 0.2f;					   //Duration of timer for recast if issues occur.

	UPROPERTY()
		int CurrentCheckpoint = 0;						   //is checked to stop checkpoint backtrack.
	UPROPERTY(Replicated)
		FVector CurrentSpawnLocation = { 0.0f,0.0f,0.0f }; //Location of current checkpoint spawn.
	UPROPERTY(Replicated, EditAnywhere)
		float ResetPositionPlaneLocation = -50.0f;		   //Height where player will be forced to restart to last checkpoint

	UPROPERTY()
		ACourseGameModeBase* CourseGameModeRef;			   //Was used to check if playable, Ran out of time so removed atm.
};
