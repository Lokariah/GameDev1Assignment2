// Fill out your copyright notice in the Description page of Project Settings.

//This got abandoned due to time

#include "SlidingDoorActor.h"

// Sets default values
ASlidingDoorActor::ASlidingDoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlidingDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlidingDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

