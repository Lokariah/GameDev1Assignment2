// Fill out your copyright notice in the Description page of Project Settings.

//This got abandoned due to time. 

#include "CourseGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MovieSceneSequencePlayer.h"
#include "Engine/TargetPoint.h"
#include "Net/UnrealNetwork.h"

void ACourseGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		NetUpdateFrequency = 5;
		SetReplicates(true);
	}

	//if (SequencePlayer == nullptr && LevelSequenceObject)SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequenceObject, FMovieSceneSequencePlaybackSettings(), LevelSequenceActorClass);
	//if (SequencePlayer) {
	//	if(LevelSequenceActorClass) LevelSequenceActorClass->SetReplicatePlayback(true);
	//	SequencePlayer->Play();
	//	GetWorld()->GetTimerManager().SetTimer(BeginCourseTimer, this, &ACourseGameModeBase::BeginCourseTimeUp, BeginCourseDuration, false);
	//}
	//else {
	//	BeginCourseTimeUp();
	//}
}

bool ACourseGameModeBase::GetPlayable()
{
	return bIsPlayable;
}

void ACourseGameModeBase::BeginCourseTimeUp()
{
	GetWorld()->GetTimerManager().SetTimer(BeginPlayTimer, this, &ACourseGameModeBase::BeginPlayTimeUp, BeginPlayDuration, false);

}

void ACourseGameModeBase::BeginPlayTimeUp_Implementation()
{
	bIsPlayable = true;
}

void ACourseGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, bIsPlayable, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, BeginCourseTimer, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, BeginPlayTimer, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, SequencePlayer, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, LevelSequenceObject, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ACourseGameModeBase, LevelSequenceActorClass, COND_SimulatedOnly);
}