// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"


class FUICommandList;
class FExtender;
class SDockTab;
class FSpawnTabArgs;
class FMenuBarBuilder;
class FToolBarBuilder;
class FMenuBuilder;

DECLARE_LOG_CATEGORY_EXTERN(JiraForUnrealLog,Log,Log);

class FJiraForUnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override; 
	virtual void ShutdownModule() override;

	void BindCommands();

	/*OpenEditorUtilityWidget*/
	static void OpenEditorUtilityWidget(FString AssetPath);
	void BuildMenu();
private:

	TSharedPtr<FExtender> MenuExtender;
	TSharedPtr<FUICommandList> UICommandList;
};
