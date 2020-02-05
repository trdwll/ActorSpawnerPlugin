/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawnManager.generated.h"

/**
 * This class/actor is only spawned on the Server and is to not be accessible anywhere else.
 */
UCLASS(NotBlueprintable, notplaceable)
class ACTORSPAWNERPLUGIN_API AActorSpawnManager final : public AActor
{
	GENERATED_BODY()

	class UActorSpawnerPluginSettings* m_Settings;

	/** Array of AActorSpawnPoints that are in the world. */
	TArray<class AActor*> m_SpawnPoints;

	/** Array of AActorAreaSpawns that are in the world. */
	TArray<class AActor*> m_AreaSpawnPoints;

	/** How much actor has been spawned in the level. - This is used for debugging and logging. */
	uint32 m_NumActorsSpawned;

	/** Handle spawning of the actors in the world. */
	UFUNCTION()
	void SpawnActors();

	/** Check the actors in the world and count the amount of them that were spawned by this manager. */
	bool CantSpawnMoreActors();

	/** Is this the first time that this is being ran? */
	bool m_bFirstTimeRunning;

public:	
	AActorSpawnManager();

	virtual void BeginPlay() override;

	/** Get the number of actors spawned in the world. */
	FORCEINLINE uint32 GetNumActorsSpawned() const { return m_NumActorsSpawned; }
};

