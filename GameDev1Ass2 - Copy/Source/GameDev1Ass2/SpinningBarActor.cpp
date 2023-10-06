// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningBarActor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASpinningBarActor::ASpinningBarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpinningBarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	SetRootComponent(SpinningBarMesh);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASpinningBarActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority()) {
		NetUpdateFrequency = 5;
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called every frame
void ASpinningBarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float adjustedRotationAmount = RotationAmount;
	if (!bRotateClockwise) adjustedRotationAmount *= -1.0f;
	/*if (HasAuthority()) {*/
		AddActorLocalRotation(FRotator(0.0f, adjustedRotationAmount * DeltaTime, 0.0f));
	/*}*/
}

void ASpinningBarActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ASpinningBarActor, RotationAmount, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ASpinningBarActor, bRotateClockwise, COND_SimulatedOnly);
}