#include "Widget/UBugReporter.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "Misc/Base64.h"
#include "Settings/UJiraForUnrealSettings.h"

void UBugReporter::SendData(FString Summary,FString Task, FString Description)
{
	const UJiraForUnrealSettings* Settings = GetDefault<UJiraForUnrealSettings>();
	
	 FString JiraURL = Settings->JiraURL;
	
	
	 FString Username = Settings->JiraMail;
	 FString ApiToken = Settings->JiraToken;
	
	
	 FString AuthString = Username + ":" + ApiToken;
	 FString AuthHeader = "Basic " + FBase64::Encode(AuthString);
	
	
	 TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	 Request->SetURL(JiraURL);
	 Request->SetVerb("POST");
	 Request->SetHeader("Content-Type", "application/json");
	 Request->SetHeader("Authorization", AuthHeader);
	 TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	
	 TSharedPtr<FJsonObject> FieldsObject = MakeShareable(new FJsonObject());
	 FieldsObject->SetStringField("summary", Summary);

	 TSharedPtr<FJsonObject> IssueTypeObject = MakeShareable(new FJsonObject());
	 IssueTypeObject->SetStringField("name", Task); 
	 FieldsObject->SetObjectField("issuetype", IssueTypeObject);

	 TSharedPtr<FJsonObject> DescriptionObject = MakeShareable(new FJsonObject());
	 DescriptionObject->SetStringField("type", "doc");
	 DescriptionObject->SetNumberField("version", 1);
	
	 TArray<TSharedPtr<FJsonValue>> ContentArray;
	 TSharedPtr<FJsonObject> ParagraphObject = MakeShareable(new FJsonObject());
	 ParagraphObject->SetStringField("type", "paragraph");
	
	 TArray<TSharedPtr<FJsonValue>> ParagraphContent;
	 TSharedPtr<FJsonObject> TextObject = MakeShareable(new FJsonObject());
	 TextObject->SetStringField("type", "text");
	 TextObject->SetStringField("text", Description);
	
	 ParagraphContent.Add(MakeShareable(new FJsonValueObject(TextObject)));
	 ParagraphObject->SetArrayField("content", ParagraphContent);
	 ContentArray.Add(MakeShareable(new FJsonValueObject(ParagraphObject)));
	
	 DescriptionObject->SetArrayField("content", ContentArray);
	 FieldsObject->SetObjectField("description", DescriptionObject);
	
	 TSharedPtr<FJsonObject> ProjectObject = MakeShareable(new FJsonObject());
	 ProjectObject->SetStringField("key", Settings->JiraProjectKey); 
	 FieldsObject->SetObjectField("project", ProjectObject);
	 JsonObject->SetObjectField("fields", FieldsObject);
	
	 FString OutputString;
	 TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	 FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	

	 Request->SetContentAsString(OutputString);
	 Request->OnProcessRequestComplete().BindUObject( this,&UBugReporter::DataResponse);
	 Request->ProcessRequest();
}

void UBugReporter::DataResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	TicketResultResponse = FString("Ticket creation success : " + Response->GetContentAsString());
	bTicketWasSuccessful =  bWasSuccessful;
	K2_DataResponse();
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Ticket créé avec succès : %s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Ticket Error : %s"), *Response->GetContentAsString());
	}

}

void UBugReporter::OpenJira()
{
	FString jiraURL = GetDefault<UJiraForUnrealSettings>()->JiraURL;
	FString LeftSplit, RightSplit;
	jiraURL.Split(".net/",&LeftSplit ,&RightSplit,ESearchCase::IgnoreCase);
	LeftSplit += ".net/";
	FPlatformProcess::LaunchURL(*LeftSplit , nullptr, nullptr);
}
