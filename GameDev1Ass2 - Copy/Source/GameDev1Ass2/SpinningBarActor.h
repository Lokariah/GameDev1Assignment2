// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinningBarActor.generated.h"

UCLASS()
class GAMEDEV1ASS2_API ASpinningBarActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinningBarActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SpinningBarMesh;			//Mesh used to display spinning bar
	UPROPERTY(EditAnywhere, Replicated)
		float RotationAmount = 200.0f;					//Adjustable value for speed.
	UPROPERTY(EditAnywhere, Replicated)
		bool bRotateClockwise = true;					//Invert rotationSpeed if false.
};
