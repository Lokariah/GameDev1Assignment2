// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointZoneActor.h"
#include "Kismet/GameplayStatics.h"
#include "CustomPlayerController.h"

// Sets default values
ACheckpointZoneActor::ACheckpointZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint"));
	SetRootComponent(CheckpointMesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	CollisionBox->SetupAttachment(CheckpointMesh);
	CollisionBox->SetBoxExtent(FVector(200.0f, 1000.0f, 250.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 125.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ACheckpointZoneActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointZoneActor::OnOverlapBegin);
}

// Called every frame
void ACheckpointZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointZoneActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks if a player overlaps, if first time and they're not from a future checkpoint, sets there checkpoint as this.
	characterRef = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if ((!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) && characterRef->GetCurrentCheckpoint() < CheckpointNo) {
		TempActorsHit.Emplace(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint Hit"));
		characterRef->ServerSetSpawnLocation(GetActorLocation(), CheckpointNo);
	}
}

