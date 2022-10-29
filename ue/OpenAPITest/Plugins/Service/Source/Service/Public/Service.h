// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "OpenAPIDefaultApi.h"
#include "OpenAPIDefaultApiOperations.h"

class FServiceModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<IConsoleCommand*> Commands;

	static void HandleHelloResponse(const OpenAPI::OpenAPIDefaultApi::HelloOperationResponse& Response);
	static void HandleUploadResponse(const OpenAPI::OpenAPIDefaultApi::UploadFileResponse& Response);
	static void OnScreenshotCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors);

	static FDelegateHandle ScreenShotCapturedDelegate;
	static OpenAPI::OpenAPIDefaultApi::FHelloOperationDelegate HandleResponseDelegate;
	static OpenAPI::OpenAPIDefaultApi::FUploadFileDelegate UploadResponseDelegate;
	static bool bIsBusyUpload;
	static TSharedPtr<OpenAPI::OpenAPIDefaultApi> Api;
};
