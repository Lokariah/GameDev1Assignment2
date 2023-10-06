// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CheckpointZoneActor.generated.h"

class ACustomPlayerController;

UCLASS()
class GAMEDEV1ASS2_API ACheckpointZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointZoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Triggers checkpoint set if first time overlap and is wanted checkpoint.
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CheckpointMesh;						 //Visual representation of Checkpoint.
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;						 //Used to check if player has entered the checkpoint to trigger update.
	UPROPERTY() 
		TArray<AActor*> TempActorsHit;						 //Adds actors to list to check against if walked through.
	UPROPERTY(EditAnywhere)
		int CheckpointNo = 0;								 //Checkpoint Number to check against player's current checkpoint.
	UPROPERTY()
		ACustomPlayerController* characterRef;				 //Used to set checkpoint in character.
};
