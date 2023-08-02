// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootaWeaponComponent.generated.h"

class AShootaBaseWeapon;

UCLASS()
class SHOOTA_API UShootaWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UShootaWeaponComponent();

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AShootaBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = "socket_gun";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AShootaBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
