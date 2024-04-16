// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"
#include "Kismet/GameplayStatics.h"
#include "Galaga_USFX_L01Projectile.h"
#include "NaveEnemigaCaza.generated.h"




/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveEnemigaCaza : public ANaveEnemiga
{
	GENERATED_BODY()
private:
	int cantidadBombas;



public:
	ANaveEnemigaCaza();
	FVector GunOffsetEnemy;

	FORCEINLINE int GetCantidadBombas() const { return cantidadBombas; }
	FORCEINLINE void SetCantidadBombas(int _cantidadBombas) { cantidadBombas = _cantidadBombas; }
protected:
	virtual void Mover(float DeltaTime);
	virtual void Disparar() ;
	virtual void ShotTimerExpiredEnemy();

	virtual void BeginPlay() override;	

	FTimerHandle TimerHandleEnemy;
	
	/* Flag to control firing  */
	uint32 bCanFireEnemy ;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	
	float VelocidadProyectil = 1000.0f;;
	float Speed;
};
