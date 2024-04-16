// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaCazaAlfa.h"

ANaveEnemigaCazaAlfa::ANaveEnemigaCazaAlfa()
{
}

void ANaveEnemigaCazaAlfa::Tick(float DeltaTime)
{
}

void ANaveEnemigaCazaAlfa::Mover()
{
}

void ANaveEnemigaCazaAlfa::Disparar()
{

	// Obtén la ubicación de la nave caza para spawnear el proyectil
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * -150 + FVector(-10.0f, 0.0f, 0.0f);//distancia de disparo

	// Spawnear el proyectil
	AGalaga_USFX_L01Projectile* NewProjectile = GetWorld()->SpawnActor<AGalaga_USFX_L01Projectile>(AGalaga_USFX_L01Projectile::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	if (NewProjectile)
	{
		VelocidadProyectil = 1000.0f;
		// Modificar dirección y velocidad del proyectil según sea necesario
		FVector SpawnDirection = FVector(-0.50f, 0.0f, 0.0f);
		NewProjectile->SetProjectileVelocity(SpawnDirection * VelocidadProyectil);

		// Modificar otras propiedades del proyectil según sea necesario
		NewProjectile->SetProjectileScale(FVector(1.0f, 3.0f, 2.0f)); // Ejemplo: escalar el proyectil
	}
}

void ANaveEnemigaCazaAlfa::BeginPlay()
{
	Super::BeginPlay();
	TimeHandle = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ANaveEnemigaCazaAlfa::Disparar, 0.3f, true);
}

