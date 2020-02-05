/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#include "ActorSpawnManager.h"
#include "ActorSpawnPoint.h"
#include "ActorAreaSpawn.h"
#include "ActorSpawner.h"
#include "ActorSpawnerPluginSettings.h"
#include "ASPBPL.h"
#include "ActorSpawnerInterface.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "GeneratedCodeHelpers.h"
#include "Engine.h"

#if ENGINE_MINOR_VERSION <= 23
#define ISAUTHORITY (Role == ROLE_Authority)
#elif ENGINE_MINOR_VERSION >= 24
#define ISAUTHORITY (GetLocalRole() == ROLE_Authority)
#endif

AActorSpawnManager::AActorSpawnManager()
{
	SetReplicates(true);
	bAlwaysRelevant = true;
}

void AActorSpawnManager::BeginPlay()
{	
	// Get the settings for the plugin
	m_Settings = GetMutableDefault<UActorSpawnerPluginSettings>();

	/** We want to gather the actor spawns before we call the default BeginPlay() */
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorSpawnPoint::StaticClass(), m_SpawnPoints);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorAreaSpawn::StaticClass(), m_AreaSpawnPoints);

	// Set true since this is the first time this is running.
	m_bFirstTimeRunning = true;

	/** Start spawning actor */
	SpawnActors();

	Super::BeginPlay();

	// If respawning is enabled then create a timer on the authority
	if (m_Settings->m_bEnableActorRespawn)
	{
		if (ISAUTHORITY)
		{
			FTimerHandle ActorRespawnTimer;
			GetWorldTimerManager().SetTimer(ActorRespawnTimer, this, &AActorSpawnManager::SpawnActors, m_Settings->m_ActorRespawnTime, true, m_Settings->m_ActorRespawnTime);
		}
	}
}

void AActorSpawnManager::SpawnActors()
{
	if (ISAUTHORITY)
	{
		LOG("Spawning actors in the level");
		if (m_Settings->m_bEnableActorRespawn || m_bFirstTimeRunning)
		{
			/** Don't spawn anymore actor in the world if we're above the MAX. */
			if (CantSpawnMoreActors())
			{
				LOG("The amount of actors that have spawned exceed the amount of MaxSpawnableActors. Please edit the MaxSpawnableActors value or refrain from spawning too many actors.");
				return;
			}

			// Get the character class from the config else set to the default ACharacter class
			UClass* const CharacterClass = m_Settings->m_CharacterClass == nullptr ? ACharacter::StaticClass() : m_Settings->m_CharacterClass->StaticClass();

			// Create a new array and append both arrays of spawnpoints together to avoid having to iterate over 2 arrays
			TArray<AActor*> NewArray;
			NewArray.Append(m_SpawnPoints);
			NewArray.Append(m_AreaSpawnPoints);

			for (AActor* const actor : NewArray)
			{
				// This check is somewhat redundant since we're getting the spawnpoints and spawnareas in the world.
				if (!actor->GetClass()->ImplementsInterface(UActorSpawnerInterface::StaticClass()))
				{
					LOG("Actor '%s' doesn't implement the interface 'IActorSpawnerInterface'.", *actor->GetName());
					return;
				}

				// Get the actors that are overlapping the spawnpoint
				TArray<AActor*> OutActors = IActorSpawnerInterface::Execute_GetOverlappedActors(actor);

				// Determine if it's ok to spawn (check if any actors in your Blacklist are present in the overlap)
				bool bNotOkToSpawn = OutActors.ContainsByPredicate([&](const AActor* actor)
				{
					return m_Settings->m_ActorBlacklist.Contains(actor->GetClass());
				});

				if (!bNotOkToSpawn || m_bFirstTimeRunning)
				{
					TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
					TArray<AActor*> IgnoredActors;

					// Check if any players are nearby
					bool bCharactersNear = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), actor->GetActorLocation(), m_Settings->m_RespawnRadius * 2, ObjectTypes, CharacterClass, IgnoredActors, OutActors);
					if (m_Settings->m_bRespawnIfCharactersNearby || !bCharactersNear || m_bFirstTimeRunning)
					{
						// Spawn actors
						IActorSpawnerInterface::Execute_SpawnActors(actor);
					}
				}
			}
		}

		// Run this bool method just to set the m_NumActorsSpawned since it's the first time running. We want to log the amount of actors after the first run
		if (m_bFirstTimeRunning)
		{
			CantSpawnMoreActors();
		}
		
		m_bFirstTimeRunning = false;

		LOG("Spawned %d total actors in the world.", m_NumActorsSpawned);
	}
}

bool AActorSpawnManager::CantSpawnMoreActors()
{
	// Get all of the actors in the world that have a tag
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), FName(TEXT("TRDWLL_ASP")), OutActors);
	m_NumActorsSpawned = (uint32)OutActors.Num();

	return (uint32)OutActors.Num() >= m_Settings->m_MaxSpawnableActors;
}

