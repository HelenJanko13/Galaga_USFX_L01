// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaCazaAlfa.h"

ANaveEnemigaCazaAlfa::ANaveEnemigaCazaAlfa()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));

	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
}

void ANaveEnemigaCazaAlfa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}

void ANaveEnemigaCazaAlfa::Mover(float DeltaTime)
{

	FVector PosicionActual = GetActorLocation();
	FVector NuevaPosicion = FVector(PosicionActual.X - 100 * DeltaTime * velocidad, PosicionActual.Y, PosicionActual.Z);

	SetActorLocation(NuevaPosicion);


	if (NuevaPosicion.X < limiteX)
	{

		SetActorLocation(FVector(1500.0f, PosicionActual.Y, PosicionActual.Z));

	}
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
		float RandomAngle = FMath::RandRange(0.0f, 360.0f);
		FVector SpawnDirection = FVector(FMath::Cos(RandomAngle), FMath::Sin(RandomAngle), 0.0f);
		NewProjectile->SetProjectileVelocity(SpawnDirection * VelocidadProyectil);

		// Modificar otras propiedades del proyectil según sea necesario
		NewProjectile->SetProjectileScale(FVector(1.0f, 3.0f, 2.0f)); 
	}
}

void ANaveEnemigaCazaAlfa::BeginPlay()
{
	Super::BeginPlay();
	TimerHandleEnemy = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimerHandleEnemy, this, &ANaveEnemigaCazaAlfa::Disparar, 0.3f, true);
}

