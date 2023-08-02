// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ShootaBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
AShootaBaseWeapon::AShootaBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void AShootaBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AShootaBaseWeapon::Fire() {
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire"))
}
