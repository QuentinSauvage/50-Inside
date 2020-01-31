// Fill out your copyright notice in the Description page of Project Settings.

#include"Matinee/MatineeActor.h"
#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);

	bIsOpen = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Enter!"));

	if (OtherActor && OtherActor != this)
	{
		if (!bIsOpen && mat) {
			bIsOpen = true;
			mat->Play();

		}

	}
}

void ADoor::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (bIsOpen) {
			bIsOpen = false;
			//mat.rew
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("outer!"));

	}
}