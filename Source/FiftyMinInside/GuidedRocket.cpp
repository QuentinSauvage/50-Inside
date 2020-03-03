// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedRocket.h"
#include "GuidedRocketLauncher.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "BulletExplosion.h"

AGuidedRocket::AGuidedRocket()
{
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->ProjectileGravityScale = 0.f;

	MaterialInstance = CreateDefaultSubobject<UMaterial>("Material");

	OnActorHit.AddDynamic(this, &AGuidedRocket::OnBulletHit);
}

void AGuidedRocket::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->SetMaterial(0, Cast<UMaterialInterface>(MaterialInstance));

}

void AGuidedRocket::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this) {
		APawn* Pawn = Cast<APawn>(OtherActor);
		if (Pawn) {
			float DamageDealed = UGameplayStatics::ApplyPointDamage(OtherActor, DamageValue, GetActorLocation(), Hit, nullptr, this, DamageType);
		}
	}
	if (BulletExplosion)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		FTransform ExplosionTransform;
		ExplosionTransform.SetLocation(GetActorLocation());
		ABulletExplosion* Explosion = GetWorld()->SpawnActor <ABulletExplosion>(BulletExplosion, ExplosionTransform, SpawnParams);
		Explosion->Init(DamageType, DamageValue);
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, GetActorLocation());
	
	AGuidedRocketLauncher* launcher = Cast<AGuidedRocketLauncher>(this->GetOwner());
	if (launcher)
	{
		launcher->ResetFiring();
	}
	this->ClearRenderTexture();
	Destroy();
}