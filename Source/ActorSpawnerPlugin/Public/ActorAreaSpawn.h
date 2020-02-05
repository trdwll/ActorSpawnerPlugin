/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ASPBPL.h"
#include "ActorSpawner.h"
#include "ActorSpawnerInterface.h"
#include "ActorAreaSpawn.generated.h"

/**
 * This class is used when actors should be spawned in an area (square) 
 */
UCLASS(BlueprintType)
class ACTORSPAWNERPLUGIN_API AActorAreaSpawn final : public AActor, public IActorSpawnerInterface
{
	GENERATED_BODY()
	
public:	
	AActorAreaSpawn();

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

	/** The maximum amount of actors that can be spawned in the area. */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Max Items in Area", meta = (ClampMin = "1", ClampMax = "500"))
	int32 m_MaxItemsInBox;

	/** The actor spawn area box component */
	UPROPERTY(EditDefaultsOnly, Category = "TRDWLL|ActorSpawnerPlugin", DisplayName = "Actor Spawn Area")
	UBoxComponent* m_ActorSpawnArea;

public:
	/** Get the actor spawnable area. */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE UBoxComponent* GetActorSpawnArea() const { return m_ActorSpawnArea; }

	/** Get the item spawn list */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE TArray<FActorItem> GetActorWhitelist() const { return m_ActorWhitelist; }

	/** Get the item spawn group. */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE FName GetActorWhitelistGroupName() const { return m_ActorWhitelistGroupName; }

	/** Get the max amount of actors that can be spawned in this area. */
	UFUNCTION(BlueprintPure, Category = "TRDWLL|ActorSpawnerPlugin")
	FORCEINLINE int32 GetMaxActorsInBox() const { return m_MaxItemsInBox; }
};
