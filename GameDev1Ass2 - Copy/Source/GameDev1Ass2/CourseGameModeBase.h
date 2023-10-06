// Fill out your copyright notice in the Description page of Project Settings.

//This got abandoned due to time. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "CourseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS2_API ACourseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		bool GetPlayable();
private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	UPROPERTY(Replicated)
		bool bIsPlayable = false;

	UFUNCTION()
		void BeginCourseTimeUp();
	UFUNCTION(Server, Reliable)
		void BeginPlayTimeUp();

	UPROPERTY(Replicated)
		FTimerHandle BeginCourseTimer;
	UPROPERTY(EditAnywhere) 
		float BeginCourseDuration = 20.0f;
	UPROPERTY(Replicated)
		FTimerHandle BeginPlayTimer;
	UPROPERTY(EditAnywhere)
		float BeginPlayDuration = 20.0f;

	UPROPERTY(Replicated)
		ULevelSequencePlayer* SequencePlayer;
	UPROPERTY(EditAnywhere, Replicated)
		ULevelSequence* LevelSequenceObject;
	UPROPERTY(EditAnywhere, Replicated)
		ALevelSequenceActor* LevelSequenceActorClass;
};
