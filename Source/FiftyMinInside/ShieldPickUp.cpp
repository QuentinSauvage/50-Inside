// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldPickUp.h"
#include "FiftyMinInsidePawn.h"
#include "Math/UnrealMathUtility.h"

void AShieldPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor != this) {
		AFiftyMinInsidePawn* Pawn = Cast<AFiftyMinInsidePawn>(OtherActor);
		if (Pawn && Pawn->GetHealth() < 1.f) {
			Pawn->UpdateHealth(10.f);
			Destroy();
		}
	}
}