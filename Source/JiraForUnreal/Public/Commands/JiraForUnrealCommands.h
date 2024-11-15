#pragma once

#include "SlateBasics.h"
#include "Framework/Commands/Commands.h"
#include "Style/JiraForUnrealStyle.h"


class FJiraForUnrealCommands : public TCommands<FJiraForUnrealCommands>
{
public:
	FJiraForUnrealCommands(): TCommands<FJiraForUnrealCommands>
(
	TEXT("JiraForUnreal"),
	NSLOCTEXT("Contexts", "JiraForUnreal", "JiraForUnreal"),
	NAME_None,
	FJiraForUnrealStyle::GetStyleSetName()
){}
	
	
	virtual void RegisterCommands() override;

	
	TSharedPtr<FUICommandInfo> OpenJiraReporter;
};
