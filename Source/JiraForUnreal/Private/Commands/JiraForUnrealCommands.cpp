#include "Commands/JiraForUnrealCommands.h"

#define LOCTEXT_NAMESPACE "JiraForUnrealCommands"

void FJiraForUnrealCommands::RegisterCommands()
{
	UI_COMMAND(OpenJiraReporter, "Jira Reporter", "Jira Reporter Menu", EUserInterfaceActionType::Button, FInputChord());

}