// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ShootaWeaponComponent.h"
#include "Weapon/ShootaBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Player/ShootaBaseCharacter.h"

// Sets default values
UShootaWeaponComponent::UShootaWeaponComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void UShootaWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UShootaWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	AShootaBaseCharacter* Character = Cast<AShootaBaseCharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<AShootaBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetFPSkeletalMesh(), AttachmentRules, WeaponSocketName);
	CurrentWeapon->SetOwner(Character);
}

void UShootaWeaponComponent::Fire() {
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}

