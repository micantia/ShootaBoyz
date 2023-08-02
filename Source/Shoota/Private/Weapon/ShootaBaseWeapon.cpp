// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ShootaBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire"));
	MakeShot();
}

void AShootaBaseWeapon::MakeShot() {
	if (!GetWorld()) return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform MuzzleSocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector ShotStart = ViewLocation;
	const FVector ShotDirection = ViewRotation.Vector();
	const FVector ShotEnd = ShotStart + ShotDirection * ShotMaxDistance;

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(
		HitResult, ShotStart, ShotEnd,
		ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit) 
	{

		DrawDebugLine(GetWorld(), MuzzleSocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(
			GetWorld(), HitResult.ImpactPoint, 10.0f,
			24, FColor::Green, false, 5.0f);
	}
	else {
		DrawDebugLine(GetWorld(), MuzzleSocketTransform.GetLocation(), ShotEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}