// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletExplosion.generated.h"

UCLASS()
class FIFTYMININSIDE_API ABulletExplosion : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletExplosion();

	void Init(TSubclassOf<UDamageType> BulletDamageType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Components")
		class USphereComponent* Collision;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMeshComponent* Mesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
