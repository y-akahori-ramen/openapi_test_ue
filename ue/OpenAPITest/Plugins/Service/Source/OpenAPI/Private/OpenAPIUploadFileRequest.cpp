/**
 * FileServer
 * No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
 *
 * OpenAPI spec version: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIUploadFileRequest.h"

#include "OpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

void OpenAPIUploadFileRequest::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Filename.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("filename")); WriteJsonValue(Writer, Filename.GetValue());
	}
	if (Base64data.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("base64data")); WriteJsonValue(Writer, Base64data.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPIUploadFileRequest::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("filename"), Filename);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("base64data"), Base64data);

	return ParseSuccess;
}

}
