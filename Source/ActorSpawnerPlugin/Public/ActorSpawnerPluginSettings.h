/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "ActorSpawnerPluginSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class ACTORSPAWNERPLUGIN_API UActorSpawnerPluginSettings : public UObject
{
	GENERATED_BODY()
	

public:

    UActorSpawnerPluginSettings();

    /** If true, allow actors to respawn. */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Enable Actor Respawning")
	bool m_bEnableActorRespawn = true;

	/** What's the maximum amount of actors that can be spawned by this? */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Max Spawnable Actors")
	uint32 m_MaxSpawnableActors = 250000;

	/** The time to wait before respawning actors if allowed. (seconds) */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Actor Respawn Time")
	float m_ActorRespawnTime = 1800.0f;

	/** If true, actors can respawn if a character is nearby else actors can't respawn if a character is nearby. */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Allow Respawn if Characters Nearby")
	bool m_bRespawnIfCharactersNearby = false;

	/** The distance that characters must be for the actors to respawn. */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Actor Respawn Radius")
	float m_RespawnRadius = 500.0f;

	/** The character class that you want to look for when respawning actors. (if a character of this class is in the radius respawn or don't respawn as per m_bRespawnIfCharactersNearby) */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Character Class")
	TSubclassOf<class ACharacter> m_CharacterClass;

	/** The array of classes that you want to look for when respawning actors. (if these actors are in the radius either respawn or don't respawn as per m_bEnableActorRespawn) */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Actor Blacklist Classes")
	TArray<TSubclassOf<class AActor>> m_ActorBlacklist;

	/** The datatable that stores groups of actors to spawn from spawnpoints or spawnareas. */
	UPROPERTY(EditAnywhere, config, Category = General, DisplayName = "Actor Group DataTable")
	FSoftObjectPath m_ActorGroupDataTable;
};
