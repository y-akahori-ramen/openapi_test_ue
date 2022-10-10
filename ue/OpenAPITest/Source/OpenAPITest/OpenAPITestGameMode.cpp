// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenAPITestGameMode.h"
#include "OpenAPITestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOpenAPITestGameMode::AOpenAPITestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
