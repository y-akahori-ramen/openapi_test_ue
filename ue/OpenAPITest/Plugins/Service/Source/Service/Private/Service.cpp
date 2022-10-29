// Copyright Epic Games, Inc. All Rights Reserved.

#include "Service.h"

#include "ImageUtils.h"
#include "OpenAPIHelpers.h"


#define LOCTEXT_NAMESPACE "FServiceModule"

FDelegateHandle FServiceModule::ScreenShotCapturedDelegate;
OpenAPI::OpenAPIDefaultApi::FHelloOperationDelegate FServiceModule::HandleResponseDelegate;
OpenAPI::OpenAPIDefaultApi::FUploadFileDelegate FServiceModule::UploadResponseDelegate;
bool FServiceModule::bIsBusyUpload = false;
TSharedPtr<OpenAPI::OpenAPIDefaultApi> FServiceModule::Api;


void FServiceModule::StartupModule()
{
	using namespace OpenAPI;
	HandleResponseDelegate = OpenAPIDefaultApi::FHelloOperationDelegate::CreateStatic(&FServiceModule::HandleHelloResponse);
	UploadResponseDelegate = OpenAPIDefaultApi::FUploadFileDelegate::CreateStatic(&FServiceModule::HandleUploadResponse);
	ScreenShotCapturedDelegate = UGameViewportClient::OnScreenshotCaptured().AddStatic(&FServiceModule::OnScreenshotCaptured);
	Api = MakeShared<OpenAPIDefaultApi>();
	Api->SetURL("localhost:3000");

	Commands.Add(IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("Hello"),
		TEXT("Hello"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
		{
			const OpenAPIDefaultApi::HelloOperationRequest RequestBody;
			Api->HelloOperation(RequestBody, HandleResponseDelegate);
		}),
		ECVF_Default
	));

	Commands.Add(IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("Upload"),
		TEXT("Upload"),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
		{
			if (bIsBusyUpload)
			{
				UE_LOG(LogTemp, Warning, TEXT("Upload Command is busy. Please try again later."));
			}
			else
			{
				FScreenshotRequest::RequestScreenshot(false);
				bIsBusyUpload = true;
			}
		}),
		ECVF_Default
	));
}

void FServiceModule::ShutdownModule()
{
	UGameViewportClient::OnScreenshotCaptured().Remove(ScreenShotCapturedDelegate);

	for (IConsoleCommand* Command : Commands)
	{
		IConsoleManager::Get().UnregisterConsoleObject(Command);
	}
	Commands.Reset();
}

void FServiceModule::HandleHelloResponse(const OpenAPI::OpenAPIDefaultApi::HelloOperationResponse& Response)
{
	UE_LOG(LogTemp, Log, TEXT("Handle hallo response."));
	if (Response.IsSuccessful())
	{
		UE_LOG(LogTemp, Log, TEXT("Success. message: %s"), *Response.Content.Message.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed. SutatusCode: %d"), Response.GetHttpResponseCode());
	}
}

void FServiceModule::HandleUploadResponse(const OpenAPI::OpenAPIDefaultApi::UploadFileResponse& Response)
{
	UE_LOG(LogTemp, Log, TEXT("Handle upload response."));
	bIsBusyUpload = false;
}

void FServiceModule::OnScreenshotCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors)
{
	using namespace OpenAPI;

	UE_LOG(LogTemp, Log, TEXT("OnScreenshotCaptured"));

	OpenAPIDefaultApi::UploadFileRequest RequestBody;

	FString ImageName;
	FFileHelper::GenerateDateTimeBasedBitmapFilename(TEXT("OpenApiTestScreenShot"), TEXT("png"), ImageName);
	RequestBody.OpenAPIUploadFileRequest.Filename = ImageName;

	TArray64<uint8> PngData;
	FImageUtils::PNGCompressImageArray(Width, Height, Colors, PngData);
	RequestBody.OpenAPIUploadFileRequest.Base64data = FBase64::Encode(PngData.GetData(), PngData.Num());

	Api->UploadFile(RequestBody, UploadResponseDelegate);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FServiceModule, Service)
