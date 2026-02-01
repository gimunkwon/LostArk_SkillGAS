#pragma once

#include "CoreMinimal.h"

// GAS 표준 매크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Collision 채널
#define COLLISION_PLAYER		ECC_GameTraceChannel1
#define COLLISION_MONSTER		ECC_GameTraceChannel2
#define COLLISION_ENVIRONMENT	ECC_GameTraceChannel3