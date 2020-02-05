/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorSpawnerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UActorSpawnerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Added to ActorAreaSpawn and ActorSpawnPoint
 */
class ACTORSPAWNERPLUGIN_API IActorSpawnerInterface
{
	GENERATED_BODY()

public:
	/** Spawn actors */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TRDWLL|ActorSpawnerPlugin")
	void SpawnActors();

	/** Get the whitelist from the specified actor spawner. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TRDWLL|ActorSpawnerPlugin")
	TArray<struct FActorItem> GetWhitelist() const;

	/** Get the actors that are overlapping the radius of the spawner. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TRDWLL|ActorSpawnerPlugin")
	TArray<AActor*> GetOverlappedActors() const;
};
