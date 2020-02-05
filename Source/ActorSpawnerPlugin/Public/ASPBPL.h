/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"

#include "ActorSpawner.h"
#include "ActorSpawnerPluginSettings.h"
#include "ASPBPL.generated.h"

/**
 * Just a Blueprint Function Library with some static methods that we use in this plugin
 */
UCLASS()
class ACTORSPAWNERPLUGIN_API UASPBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Generate a random point in a radius
	 *
	 * @param	SpawnLocation	Initial starting point for the radius
	 * @param	MinRadius		Min radius size
	 * @param	MaxRadius		Mad radius size
	 */
	UFUNCTION(BlueprintPure, Category = "Actor Spawner Plugin|BPL")
	static FORCEINLINE FVector GetRandomLocationInRadius(FVector SpawnLocation = FVector(0.0f), float MinRadius = 500.0f, float MaxRadius = 500.0f)
	{
		float random1 = FMath::RandRange(0.0f, 360.0f);
		float random2 = FMath::RandRange(MinRadius, MaxRadius);

		float sin_v = FMath::Sin(random1) * random2;
		float cos_v = FMath::Cos(random1) * random2;

		return SpawnLocation + FVector(sin_v, cos_v, 0.0f);
	}

	/**
	 * Generate a random point in a box
	 *
	 * @param	Origin			Initial starting point for the box
	 * @param	BoxExtent		Box dimension
	 */
	UFUNCTION(BlueprintPure, Category = "Actor Spawner Plugin|BPL")
	static FORCEINLINE FVector GetRandomLocationInBox(FVector Origin, FVector BoxExtent)
	{
		const FVector BoxMin = Origin - BoxExtent;
		const FVector BoxMax = Origin + BoxExtent;
		return FMath::RandPointInBox(FBox(BoxMin, BoxMax));
	}

	/**
	 * Determine the probability
	 * 
	 * @param float percent The percentage that you want to compare with
	 * @param float min_percent The min percent
	 * @param float max_percent The max percent
	 */
	UFUNCTION(BlueprintPure, Category = "Actor Spawner Plugin|BPL")
	static FORCEINLINE bool DetermineProbability(float percent, float min_percent = 0.0f, float max_percent = 100.0f)
	{
		if (percent == max_percent) return true;
		if (percent <= min_percent) return false;

		return percent >= FMath::FRandRange(min_percent, max_percent);
	}

	/**
	 * Get the spawn group of actors by id
	 *
	 * @param FName GroupID The ID to get the group
	 */
	static FORCEINLINE FActorSpawnGroup GetActorSpawnGroup(FName GroupID)
	{
		UActorSpawnerPluginSettings* const Settings = GetMutableDefault<UActorSpawnerPluginSettings>();

		if (Settings)
		{
			UDataTable* const Table = Cast<UDataTable>(Settings->m_ActorGroupDataTable.TryLoad());
			if (Table)
			{
				return *Table->FindRow<FActorSpawnGroup>(GroupID, "");
			}
		}

		return FActorSpawnGroup();
	}
};
