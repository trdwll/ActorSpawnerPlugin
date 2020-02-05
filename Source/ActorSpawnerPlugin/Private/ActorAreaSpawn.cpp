/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#include "ActorAreaSpawn.h"

#include "ActorSpawner.h"
#include "ASPBPL.h"

#include "Kismet/KismetSystemLibrary.h"

AActorAreaSpawn::AActorAreaSpawn()
{
	m_ActorSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("ActorSpawnArea"));
	m_ActorSpawnArea->InitBoxExtent(FVector(180.0f, 180.0f, 20.0f));
	m_ActorSpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = m_ActorSpawnArea;

	m_MaxItemsInBox = 20;

	SetReplicates(true);
}

void AActorAreaSpawn::BeginPlay()
{
	Super::BeginPlay();

#ifdef _DEBUG
	DrawDebugBox(GetWorld(), this->GetActorLocation(), this->GetActorSpawnArea()->GetScaledBoxExtent(), FColor::Blue, false, 30.0f);
#endif // _DEBUG
}


void AActorAreaSpawn::SpawnActors_Implementation()
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
			if (LocalCount == GetMaxActorsInBox())
			{
				break;
			}

			/** Determine if the item can be spawned or not. */
			if (UASPBPL::DetermineProbability(ItemToSpawn.Probability))
			{
				FVector Dimension = GetActorSpawnArea()->GetScaledBoxExtent();

				/** Get the transform/location for the item. */
				FTransform Transform = FTransform(FRotator(0.0f), UASPBPL::GetRandomLocationInBox(GetActorLocation(), Dimension), FVector(1.0f));

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

TArray<AActor*> AActorAreaSpawn::GetOverlappedActors_Implementation() const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoredActors;
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation(), GetActorSpawnArea()->GetScaledBoxExtent(), ObjectTypes, AActor::StaticClass(), IgnoredActors, OutActors);

	return OutActors;
}