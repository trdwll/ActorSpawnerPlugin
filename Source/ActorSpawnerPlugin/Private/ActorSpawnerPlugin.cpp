/**
 * Copyright 2019-2020 - Russ 'trdwll' Treadwell https://trdwll.com
 */
#include "ActorSpawnerPlugin.h"

#include "ActorSpawnerPluginSettings.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FActorSpawnerPluginModule"

void FActorSpawnerPluginModule::StartupModule()
{
	RegisterSettings();
}

void FActorSpawnerPluginModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

bool FActorSpawnerPluginModule::SupportsDynamicReloading()
{
	return true;
}

bool FActorSpawnerPluginModule::HandleSettingsSaved()
{
#if WITH_EDITOR
	UActorSpawnerPluginSettings* Settings = GetMutableDefault<UActorSpawnerPluginSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}
#endif // WITH_EDITOR
	return true;
}

void FActorSpawnerPluginModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("ActorSpawner",
			LOCTEXT("RuntimeWDCategoryName", "ActorSpawner"),
			LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the ActorSpawner game module"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Project", "ActorSpawner",
			LOCTEXT("RuntimeGeneralSettingsName", "ActorSpawner"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configure Actor Spawner Settings"),
			GetMutableDefault<UActorSpawnerPluginSettings>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FActorSpawnerPluginModule::HandleSettingsSaved);
		}
	}
#endif // WITH_EDITOR
}

void FActorSpawnerPluginModule::UnregisterSettings()
{
#if WITH_EDITOR
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Project", "ActorSpawner");
	}
#endif // WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FActorSpawnerPluginModule, ActorSpawnerPlugin)