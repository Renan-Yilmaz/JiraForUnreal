#include "Settings/UJiraForUnrealSettings.h"


UJiraForUnrealSettings::UJiraForUnrealSettings(const FObjectInitializer& ObjectInitializer)
{
	JiraURL = TEXT("https://[YOURINSTANCENAME].atlassian.net/rest/api/3/issue");
}
#if WITH_EDITOR

void UJiraForUnrealSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
		// Try to Rebuild editor menu to handle change in settings but not seems to work
		// if (PropertyChangedEvent.Property == nullptr)
		// {
		// 	return;
		// }
		// IBHHEditorModule Editor = FModuleManager::Get().GetModuleChecked<IBHHEditorModule>("BigHelmetHeroesEditor");
		// Editor.BindCommands();
		// Editor.BuildMenu();
}

#endif	
