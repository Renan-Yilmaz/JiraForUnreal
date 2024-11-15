#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UJiraForUnrealSettings.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, config=Editor,DefaultConfig, meta =(DisplayName ="Jira Setting",CategoryName ="Jira Setting"))
class UJiraForUnrealSettings : public UObject
{
	GENERATED_BODY()

	UJiraForUnrealSettings(const FObjectInitializer& ObjectInitializer);
public:

	/*
	 * The URL of the jira instance that you want to access  EXAMPLE : "https://[YOURINSTANCENAME].atlassian.net/rest/api/3/issue"
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, config, Category = "Jira Settings")
	FString JiraURL;

	/*
 * The project Key that you want to access you can find it here: https://your-instance-jira.atlassian.net/jira/projects
 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, config, Category = "Jira Settings")
	FString JiraProjectKey;
	
	/*
	 * Here is your token , you can create a token if you don't have one following this link : https://id.atlassian.com/manage-profile/security/api-tokens
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, config, Category = "Jira Settings",meta=(PasswordField=true))
	FString JiraToken =  "YOURTOKEN";

	/*
	 * Your email that you are using when you log in Jira 
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, config, Category = "Jira Settings")
	FString JiraMail;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	
};

