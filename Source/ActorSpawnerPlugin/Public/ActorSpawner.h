/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#pragma once
// #include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"

#include "ActorSpawner.generated.h"


USTRUCT(BlueprintType)
struct ACTORSPAWNERPLUGIN_API FActorItem : public FTableRowBase
{
	GENERATED_BODY()

	/** How many min should this spawn? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "100"), Category = "TRDWLL|ActorSpawnerPlugin")
	int32 MinQuantity;

	/** How many max should this spawn? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "100"), Category = "TRDWLL|ActorSpawnerPlugin")
	int32 MaxQuantity;

	/** Percentage that the item will spawn. (this is per item, not MaxQuantity) - if MaxQuantity is 5 it will have a % chance to spawn 5 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "100.0"), Category = "TRDWLL|ActorSpawnerPlugin")
	float Probability;

	/** The class that you want to spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TRDWLL|ActorSpawnerPlugin")
	TSubclassOf<class AActor> ObjectClass;
};

/** A group of items that can be spawned instead of setting individual items in each spawn point. */
USTRUCT(BlueprintType)
struct ACTORSPAWNERPLUGIN_API FActorSpawnGroup : public FTableRowBase
{
	GENERATED_BODY()

	/** An array of actors that will spawn from this group */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TRDWLL|ActorSpawnerPlugin")
	TArray<FActorItem> Actors;
};

// Below is some stuff used when I'm working on the plugin, feel free to remove from the codebase
// #define _DEBUG

#ifdef _DEBUG
	#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Orange, CUR_CLASS_LINE + ": TRDWLL/ActorSpawnerPlugin: " + text)
	#define LOG(str, ...) UE_LOG(LogTemp, Log, TEXT("%s: %s"), *CUR_CLASS_LINE, *FString::Printf(TEXT(str), ##__VA_ARGS__))

	/** Current Class where this is called! */
	#define CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

	/** Current Function Name where this is called! */
	#define CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

	/** Current Line Number in the code where this is called! */
	#define CUR_LINE  (FString::FromInt(__LINE__))

	/** Current Class and Line Number where this is called! */
	#define CUR_CLASS_LINE (CUR_CLASS + "(" + CUR_LINE + ")")
#include "DrawDebugHelpers.h"
#else
	#define PRINT(text) 
	#define LOG(str, ...) UE_LOG(LogTemp, Log, TEXT("TRDWLL/ActorSpawnerPlugin: %s"), *FString::Printf(TEXT(str), ##__VA_ARGS__))
#endif