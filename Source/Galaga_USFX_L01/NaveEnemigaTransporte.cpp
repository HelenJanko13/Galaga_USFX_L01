// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaCaza.h"

ANaveEnemigaTransporte::ANaveEnemigaTransporte()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);

}

void ANaveEnemigaTransporte::Mover(float DeltaTime)
{
	FVector PosicionActual = GetActorLocation();
	FVector NuevaPosicion = FVector(PosicionActual.X - 100 * DeltaTime * velocidad, PosicionActual.Y, PosicionActual.Z);

	SetActorLocation(NuevaPosicion);


	if (NuevaPosicion.X < limiteX)
	{

		SetActorLocation(FVector(1500.0f, PosicionActual.Y, PosicionActual.Z));

	}

}

void ANaveEnemigaTransporte::Disparar()
{

	// Obtén la ubicación de la nave caza para spawnear el proyectil
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * -150 + FVector(-10.0f, 0.0f, 0.0f);//distancia de disparo

	// Spawnear el proyectil
	AGalaga_USFX_L01Projectile* NewProjectile = GetWorld()->SpawnActor<AGalaga_USFX_L01Projectile>(AGalaga_USFX_L01Projectile::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

	if (NewProjectile)
	{   VelocidadProyectil = 1000.0f;
		// Modificar dirección y velocidad del proyectil según sea necesario
		FVector SpawnDirection = FVector(-2.0f, 0.0f, 0.0f); 
		NewProjectile->SetProjectileVelocity(SpawnDirection * VelocidadProyectil);

		// Modificar otras propiedades del proyectil según sea necesario
		NewProjectile->SetProjectileScale(FVector(3.0f, 3.0f, 3.0f)); // Ejemplo: escalar el proyectil
	}

}

void ANaveEnemigaTransporte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}
void ANaveEnemigaTransporte::BeginPlay()
{
	Super::BeginPlay();
	TimeHandle = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ANaveEnemigaTransporte::Disparar, 0.3f, true);
}

