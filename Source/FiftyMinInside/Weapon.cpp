#include "Weapon.h"
#include "Bullet.h"
#include "Engine/World.h"
#include "TimerManager.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	bTryFire = false;
	LastFire = 0.0f;
	DelayBetweenShots = 0.4f;

	bUseMunition = false;
	MunitionCount = 0;
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	LastFire = DelayBetweenShots;
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWeapon::GetMunitionCount()
{
	return MunitionCount;
}

float AWeapon::GetBaseMunitionCount()
{
	return BaseMunitionCount;
}

void AWeapon::SetMunitionCount(float Amount)
{
	MunitionCount = Amount;
}

int AWeapon::GetWeaponIndex()
{
	return WeaponIndex;
}

bool AWeapon::CanFire() {
	return !bTryFire;
}

void AWeapon::FireProjectile()
{
	if (BulletClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor <ABullet>(BulletClass, GetTransform(), SpawnParams);
	}
}



void AWeapon::Fire() {
	if (CanFire()) {
		bTryFire = true;
		float InGameTime = GetWorld()->GetTimeSeconds();
		if (LastFire + DelayBetweenShots > InGameTime)
		{
			//Delay shot
			GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &AWeapon::FireProjectile, LastFire + DelayBetweenShots - InGameTime, false);
		}
		else
		{
			FireProjectile();
		}

	}
}



void AWeapon::StopFire() {
	bTryFire = false;
	GetWorldTimerManager().ClearTimer(TimeHandleFiring);

}



