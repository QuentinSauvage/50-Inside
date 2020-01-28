#include "Weapon.h"
#include "TimerManager.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	bTryFire = false;
	LastFire = 0.0f;
	DelayBetweenShots = 0.4f;
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeapon::CanFire() {
	return !bTryFire;
}

void AWeapon::FireProjectile()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Pew!"));

	if (bTryFire)
	{
		GetWorld()->GetTimerManager().SetTimer(TimeHandleFiring, this, &AWeapon::FireProjectile, DelayBetweenShots, false);
	}

	LastFire = GetWorld()->GetTimeSeconds();
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



