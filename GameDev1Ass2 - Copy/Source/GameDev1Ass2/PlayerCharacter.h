// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAMEDEV1ASS2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	virtual void Tick(float DeltaTime) override;

private:
	//Sends damage notification through to controller to handle.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;					 //Camera used as main viewpoint for player.
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;				 //Spring arm to regulate and distance Main camera for a consistant experience.
};
