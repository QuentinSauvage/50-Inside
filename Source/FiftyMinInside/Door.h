// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Door.generated.h"

UCLASS()
class FIFTYMININSIDE_API ADoor : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	bool bIsOpen;

public:
	UPROPERTY(EditAnywhere)
	class AMatineeActor* mat;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// constructor sets default values for this actor's properties
	ADoor();

	// overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
