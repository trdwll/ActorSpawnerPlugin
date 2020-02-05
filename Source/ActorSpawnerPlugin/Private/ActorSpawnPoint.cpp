/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#include "ActorSpawnPoint.h"

#include "ActorSpawner.h"
#include "ASPBPL.h"

#include "Kismet/KismetSystemLibrary.h"

AActorSpawnPoint::AActorSpawnPoint()
{
	SetReplicates(true);

	m_MaxActorsInRadius = 10;

	m_MinSpawnRadius = 50.0f;
	m_MaxSpawnRadius = 250.0f;
}

void AActorSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

#ifdef _DEBUG
	DrawDebugSphere(GetWorld(), this->GetActorLocation(), this->m_MaxSpawnRadius, 12, FColor::Blue, false, 30.0f);
#endif // _DEBUG
}

void AActorSpawnPoint::SpawnActors_Implementation()
{
	/** Store a temporary count of items that's been spawned for this spawnpoint so we don't go over the max for the spawnpoint. */
	int32 LocalCount = 0;

	/** Iterate over the whitelist and begin spawning actor. */
	for (int32 i = 0; i < IActorSpawnerInterface::Execute_GetWhitelist(this).Num(); i++)
	{
		FActorItem ItemToSpawn = IActorSpawnerInterface::Execute_GetWhitelist(this)[i];

		int32 SpawnCount = FMath::RandRange(ItemToSpawn.MinQuantity, ItemToSpawn.MaxQuantity);
		for (int32 j = 0; j < SpawnCount; j++)
		{
			/** Check if the items in the radius are greater than the maximum allowed. */
			if (LocalCount == GetMaxActorsInRadius())
			{
				break;
			}

			/** Determine if the item can be spawned or not. */
			if (UASPBPL::DetermineProbability(ItemToSpawn.Probability))
			{
				/** Get the transform/location for the item. */
				FTransform Transform = FTransform(FRotator(0.0f),
					GetMinSpawnRadius() > 0.0f && GetMaxSpawnRadius() > 0.0f ?
					UASPBPL::GetRandomLocationInRadius(GetActorLocation(), GetMinSpawnRadius(), GetMaxSpawnRadius()) :
					GetActorLocation(),
					FVector(1.0f));

				AActor* const Item = GetWorld()->SpawnActorDeferred<AActor>((UClass*)ItemToSpawn.ObjectClass, Transform);
				Item->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				Item->FinishSpawning(Transform);

				if (Item)
				{
					LocalCount++;

					// Set a tag for later when we're counting how many actors the manager has spawned.
					Item->Tags.Add(FName(TEXT("TRDWLL_ASP")));
				}
			}
		}
	}
}

TArray<AActor*> AActorSpawnPoint::GetOverlappedActors_Implementation() const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoredActors;
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), GetMaxSpawnRadius(), ObjectTypes, AActor::StaticClass(), IgnoredActors, OutActors);

	return OutActors;
}
