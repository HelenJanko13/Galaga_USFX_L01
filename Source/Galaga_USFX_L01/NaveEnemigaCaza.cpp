// Fill out your copyright notice in the Description page of Project Settings.

#include "NaveEnemigaCaza.h"



ANaveEnemigaCaza::ANaveEnemigaCaza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));
	//mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);

	GunOffsetEnemy = FVector(10.f, 0.f, 0.f);
	//FireRateEnemy = 0.1f;
	bCanFireEnemy = true;

	//TiempoEntreProyectil = 1.5f;
	//TiempoUltimoProyectil = 0.0f;
	//VelocidadProyectil = 1000.0f;
}


void ANaveEnemigaCaza::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Mover(DeltaTime);

   // FVector PosicionActual = GetActorLocation();
   // FVector Desplazamiento = FVector(-1*Speed * DeltaTime,0.f,0.f);

    //FVector NuevaPosicion = FVector(PosicionActual.X + DesplazamientoX * -1, PosicionActual.Y, PosicionActual.Z);
    //SetActorLocation(PosicionActual + Desplazamiento);

   /* TiempoUltimoProyectil += DeltaTime;

    // Verificar si ha pasado el tiempo suficiente desde el último disparo
    if (TiempoUltimoProyectil >= TiempoEntreProyectil)
    {
		// Generar una dirección de disparo predefinida (por ejemplo, hacia adelante)
		//const FVector FireDirectionEnemy = GetActorForwardVector();

		// Intentar disparar un proyectil en la dirección predefinida
		Disparar();

        // Reiniciar el tiempo
        TiempoUltimoProyectil = 0.0f;
    }*/
}
  

/*void ANaveEnemigaCaza::Disparar(FVector FireDirectionEnemy)
{    
	if (bCanFireEnemy) {
		 //FRotator FireRotationEnemy = FireDirectionEnemy.Rotation();
		 FVector SpawnLocation = GetActorLocation() + GetActorForwardVector()*-100 + GunOffsetEnemy;


		UWorld* const World = GetWorld();
		if (World )
		{
			// Spawn the projectile
			AGalaga_USFX_L01Projectile* NewProjectile = World->SpawnActor<AGalaga_USFX_L01Projectile>(AGalaga_USFX_L01Projectile::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

			// Set the timer for shot expiration
			//World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpiredEnemy, this, &ANaveEnemigaCaza::ShotTimerExpiredEnemy, FireRateEnemy);
			if (NewProjectile)
			{
				// Modificar dirección y velocidad según sea necesario
				FVector SpawnDirection = FVector(-1.0f, 0.f, 0.f); // Ejemplo: disparar hacia abajo
				NewProjectile->SetProjectileVelocity(SpawnDirection * VelocidadProyectil);
				// Ajustar velocidad del proyectil
			}
			// Play the fire sound
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
		}
		bCanFireEnemy = false;
	}
}*/



void ANaveEnemigaCaza::BeginPlay()
{
	Super::BeginPlay();
	TimerHandleEnemy = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHandleEnemy, this, &ANaveEnemigaCaza::Disparar, 3.0f, true);
}

void ANaveEnemigaCaza::Disparar()
{
	if (bCanFireEnemy)
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * -100 + GunOffsetEnemy;

		UWorld* const World = GetWorld();
		if (World)
		{
			// Spawn the projectile
			AGalaga_USFX_L01Projectile* NewProjectile = World->SpawnActor<AGalaga_USFX_L01Projectile>(AGalaga_USFX_L01Projectile::StaticClass(), SpawnLocation, FRotator::ZeroRotator);

			if (NewProjectile)
			{
				FVector SpawnDirection = FVector(-1.0f, 0.f, 0.f);
				NewProjectile->SetProjectileVelocity(SpawnDirection * VelocidadProyectil);
			}

			// Play the fire sound
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
		}

		bCanFireEnemy = false;
	}
}

void ANaveEnemigaCaza::ShotTimerExpiredEnemy()
{
	bCanFireEnemy = true;
}

void ANaveEnemigaCaza::Mover(float DeltaTime)
{
	FVector PosicionActual = GetActorLocation();
	FVector NuevaPosicion = FVector(PosicionActual.X - 100 * DeltaTime * velocidad, PosicionActual.Y, PosicionActual.Z);

	SetActorLocation(NuevaPosicion);


	if (NuevaPosicion.X < limiteX)
	{

		SetActorLocation(FVector(1500.0f, PosicionActual.Y, PosicionActual.Z));

	}

}


