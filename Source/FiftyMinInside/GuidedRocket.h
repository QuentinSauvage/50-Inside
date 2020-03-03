// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/Pawn.h"
#include "GuidedRocket.generated.h"


UCLASS()
class FIFTYMININSIDE_API AGuidedRocket : public APawn
{
	GENERATED_BODY()

public:
	AGuidedRocket();

	UFUNCTION()
		virtual void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(EditAnywhere, Category = Damage)
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = Damage)
		TSubclassOf<class ABulletExplosion> BulletExplosion;

	UPROPERTY(EditAnywhere, Category = Damage)
		float DamageValue;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UMaterialInterface* MaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UParticleSystem* SpawnParticle;

	UFUNCTION(BlueprintImplementableEvent, Category = "Rendering")
		void ClearRenderTexture();

	virtual void BeginPlay() override;

};
