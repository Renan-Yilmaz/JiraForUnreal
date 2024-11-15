#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "UBugReporter.generated.h"

UCLASS()
class JIRAFORUNREAL_API UBugReporter : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category="UBugReporter")
	void OpenJira();

	UFUNCTION(BlueprintCallable,Category="UBugReporter")
	void SendData(FString Summary,FString Task, FString Description);

	void DataResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintImplementableEvent,Category="UBugReporter")
	void K2_DataResponse();
	
private:
	UPROPERTY(BlueprintReadOnly ,meta=(AllowPrivateAccess),Category="UBugReporter");
	FString TicketResultResponse;
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess),Category="UBugReporter")
	bool bTicketWasSuccessful= false;

	
	
	
	
};
