// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootaBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTA_API AShootaBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AShootaBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;

};
