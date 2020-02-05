# ActorSpawnerPlugin
__ActorSpawnerPlugin is a UE4 plugin to handle spawning actors in your level.__

## Installation

1. [Download](https://github.com/trdwll/ActorSpawnerPlugin/releases) the plugin or clone the repo
2. Copy into your _Project/Plugins_ folder
3. Open your project

## Usage

1. Create a blueprint derived of _ActorAreaSpawn_ or _ActorSpawnPoint_.
2. Create a DataTable derived of _ActorSpawnGroup_.
3. In your GameState (either in BP as follows or in C++) spawn an _AActorSpawnManager_ actor via Server.
4. Go into your __Project Settings -> Project -> ActorSpawner__ and configure the settings the way that you need to.

If you have trouble feel free to open an [Issue](https://github.com/trdwll/ActorSpawnerPlugin/issues).

## Why?
Well I originally wrote this for a survival project a couple years ago and I submitted to Epic Games for the UE Marketplace and they denied it. So I figured why not go ahead and release for free.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)