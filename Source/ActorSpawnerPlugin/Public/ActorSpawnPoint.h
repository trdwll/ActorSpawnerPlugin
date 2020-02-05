/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"

#include "ASPBPL.h"
#include "ActorSpawner.h"
#include "ActorSpawnerInterface.h"
#include "ActorSpawnPoint.generated.h"

/**
 * This class is used when actors should be spawned in radius (circle) or in one location
 */
UCLASS(BlueprintType)
class ACTORSPAWNERPLUGIN_API AActorSpawnPoint final : public ATargetPoint, public IActorSpawnerInterface
{
	GENERATED_BODY()

	AActorSpawnPoint();
	
	virtual void BeginPlay() override;

	virtual void SpawnActors_Implementation();

	virtual TArray<struct FActorItem> GetWhitelist_Implementation() const { return !GetActorWhitelistGroupName().IsNone() ? UASPBPL::GetActorSpawnGroup(GetActorWhitelistGroupName()).Actors : GetActorWhitelist(); }

	virtual TArray<AActor*> GetOverlappedActors_Implementation() const;

protected:

	/** An array of actors that this spawnpoint can spawn. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Actor Whitelist")
	TArray<FActorItem> m_ActorWhitelist;

	/** A group of actors that can be set rather than setting actors individually. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Actor Whitelist Group Name")
	FName m_ActorWhitelistGroupName;

	/** The maximum amount of actors that can be spawned by this spawnpoint. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Max Actors in Radius", meta = (ClampMin = "1", ClampMax = "255"))
	uint8 m_MaxActorsInRadius;

	/** The minimum spawn radius that this spawnpoint has. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Min Spawn Radius", meta = (ClampMin = "0", ClampMax = "2000"))
	float m_MinSpawnRadius;

	/** The maximum spawn radius that this spawnpoint has. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Max Spawn Radius", meta = (ClampMin = "0", ClampMax = "2000"))
	float m_MaxSpawnRadius;

public:
	/** Get the maximum actors to spawn in the radius */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE uint8 GetMaxActorsInRadius() const { return m_MaxActorsInRadius; }

	/** Get the minimum spawn radius */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE float GetMinSpawnRadius() const { return m_MinSpawnRadius; }

	/** Get the maximum spawn radius */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE float GetMaxSpawnRadius() const { return m_MaxSpawnRadius; }

	/** Get the item spawn list */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE TArray<FActorItem> GetActorWhitelist() const { return m_ActorWhitelist; }

	/** Get the item spawn group. */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE FName GetActorWhitelistGroupName() const { return m_ActorWhitelistGroupName; }
};
