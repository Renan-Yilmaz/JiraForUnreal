// Copyright Epic Games, Inc. All Rights Reserved.

#include "JiraForUnreal.h"

#include "EditorAssetLibrary.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "HttpModule.h"
#include "Style/JiraForUnrealStyle.h"
#include "Commands/JiraForUnrealCommands.h"
#include "Settings/UJiraForUnrealSettings.h"
#include "ISettingsModule.h"
#include "Developer/Settings/Private/SettingsContainer.h"


IMPLEMENT_MODULE(FJiraForUnrealModule, JirafForUnreal);
#define LOCTEXT_NAMESPACE "FJiraForUnrealModule"
DEFINE_LOG_CATEGORY(JiraForUnrealLog);


void FJiraForUnrealModule::StartupModule()
{

	FJiraForUnrealStyle::Initialize();
	FJiraForUnrealStyle::ReloadTextures();
	FJiraForUnrealCommands::Register();

	BindCommands();
	BuildMenu();
	IModuleInterface::StartupModule();
}

void FJiraForUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FJiraForUnrealModule::BindCommands()
{
	FString AssetPathString = "/Script/Blutility.EditorUtilityWidgetBlueprint'/JiraForUnreal/Widget/EUI_JiraBugReporter.EUI_JiraBugReporter'";
	UJiraForUnrealSettings* Settings = GetMutableDefault<UJiraForUnrealSettings>();
	UICommandList = MakeShareable(new FUICommandList);
	const FJiraForUnrealCommands& Commands = FJiraForUnrealCommands::Get();
	UICommandList->UnmapAction(Commands.OpenJiraReporter);
	UICommandList->MapAction(Commands.OpenJiraReporter,
							 FExecuteAction::CreateStatic(&FJiraForUnrealModule::OpenEditorUtilityWidget,
														 AssetPathString), FCanExecuteAction());
	
}

void FJiraForUnrealModule::OpenEditorUtilityWidget(FString AssetPath)
{
	UObject* Blueprint = UEditorAssetLibrary::LoadAsset(AssetPath);
	if (IsValid(Blueprint))
	{
		UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
		if (EditorWidget)
		{
			UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
			EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
		}
	}
}

void FJiraForUnrealModule::BuildMenu()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("Jira Plugin",
			LOCTEXT("RuntimeWDCategoryName", "Jira Plugin"),
			LOCTEXT("RuntimeWDCategoryDescription", "Jira configuration"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Jira Plugin", "Jira Configuration",
			LOCTEXT("RuntimeGeneralSettingsName", "Jira Configuration"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for Jira"),
			GetMutableDefault<UJiraForUnrealSettings>()
			);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		// if (SettingsSection.IsValid())
		// {
		// 	SettingsSection->OnModified().BindRaw(this, &FCustomSettingsModule::HandleSettingsSaved);
		// }
	}

	
	
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& MenuSection = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = MenuSection.AddEntry(
					FToolMenuEntry::InitToolBarButton(FJiraForUnrealCommands::Get().OpenJiraReporter));
				Entry.SetCommandList(UICommandList);
			
			}
		}
}

#undef LOCTEXT_NAMESPACE
