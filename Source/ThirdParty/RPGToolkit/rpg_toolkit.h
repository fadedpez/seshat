/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package github.com/fadedpez/seshat/rpgtoolkit */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h>

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */



#line 3 "core_bindings.go"

#include <stdlib.h>

#line 1 "cgo-generated-wrapper"

#line 3 "dice_bindings.go"

#include <stdlib.h>

#line 1 "cgo-generated-wrapper"

#line 3 "events_bindings.go"

#include <stdlib.h>

#line 1 "cgo-generated-wrapper"


#line 3 "simple_bindings.go"

#include <stdlib.h>

#line 1 "cgo-generated-wrapper"


/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef size_t GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
#ifdef _MSC_VER
#include <complex.h>
typedef _Fcomplex GoComplex64;
typedef _Dcomplex GoComplex128;
#else
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;
#endif

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif

extern __declspec(dllexport) int CreateCharacterComplete(char* raceDataJSON, char* classDataJSON, char* backgroundDataJSON, char* characterName, int str, int dex, int con, int intel, int wis, int cha, char** outID, char** outName, int* outLevel, int* outProficiencyBonus, char** outRaceID, char** outClassID, char** outBackgroundID, int* outStr, int* outDex, int* outCon, int* outInt, int* outWis, int* outCha, char** outSize, int* outSpeed, int* outHP, int* outMaxHP, int* outAC, int* outInitiative, char** outLanguages, char** outFeatures, char** outError);
extern __declspec(dllexport) char* GetEntityNotFoundError();
extern __declspec(dllexport) char* GetInvalidEntityError();
extern __declspec(dllexport) char* GetDuplicateEntityError();
extern __declspec(dllexport) char* GetNilEntityError();
extern __declspec(dllexport) char* GetEmptyIDError();
extern __declspec(dllexport) char* GetInvalidTypeError();
extern __declspec(dllexport) void* CreateEntityError(char* op, char* entityType, char* entityID, char* errMsg);
extern __declspec(dllexport) char* GetEntityErrorMessage(void* errPtr);
extern __declspec(dllexport) char* GetEntityErrorID(void* errPtr);
extern __declspec(dllexport) char* GetEntityErrorType(void* errPtr);
extern __declspec(dllexport) char* GetEntityErrorOp(void* errPtr);
extern __declspec(dllexport) int CreateEntityErrorComplete(char* op, char* entityType, char* entityID, char* errMsg, char** outOp, char** outType, char** outID, char** outMessage);
extern __declspec(dllexport) int ValidateEntityID(char* id);
extern __declspec(dllexport) int ValidateEntityType(char* entityType);
extern __declspec(dllexport) void FreeString(char* str);
extern __declspec(dllexport) void* CreateCryptoRoller();
extern __declspec(dllexport) int RollerRoll(void* rollerPtr, int size);
extern __declspec(dllexport) int RollerRollN(void* rollerPtr, int count, int size, int* results);
extern __declspec(dllexport) void* GetDefaultRoller();
extern __declspec(dllexport) void SetDefaultRoller(void* rollerPtr);
extern __declspec(dllexport) void* CreateRoll(int count, int size);
extern __declspec(dllexport) void* CreateRollWithRoller(int count, int size, void* rollerPtr);
extern __declspec(dllexport) int RollGetValue(uintptr_t handle);
extern __declspec(dllexport) char* RollGetDescription(uintptr_t handle);
extern __declspec(dllexport) int RollHasError(uintptr_t handle);
extern __declspec(dllexport) char* RollGetError(uintptr_t handle);
extern __declspec(dllexport) int D4Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D6Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D8Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D10Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D12Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D20Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) int D100Complete(int count, int* outValue, char** outDesc, char** outError);
extern __declspec(dllexport) void RollCleanup(uintptr_t handle);
extern __declspec(dllexport) void* CreateDiceRoller();
extern __declspec(dllexport) int RollDie(void* rollerPtr, int sides);
extern __declspec(dllexport) char* CreateEventBus();
extern __declspec(dllexport) int PublishEvent(char* eventType, char* sourceID, char* targetID, char* contextData);
extern __declspec(dllexport) char* SubscribeEvent(char* eventType, int priority);
extern __declspec(dllexport) int UnsubscribeEvent(char* subscriptionID);

// Event Type Constants - Direct exposure of toolkit constants
extern __declspec(dllexport) char* GetEventBeforeAttackRoll();
extern __declspec(dllexport) char* GetEventOnAttackRoll();
extern __declspec(dllexport) char* GetEventAfterAttackRoll();
extern __declspec(dllexport) char* GetEventBeforeDamageRoll();
extern __declspec(dllexport) char* GetEventOnTakeDamage();
extern __declspec(dllexport) char* GetEventCalculateDamage();
extern __declspec(dllexport) char* GetEventAfterDamage();
extern __declspec(dllexport) char* GetEventEntityPlaced();
extern __declspec(dllexport) char* GetEventEntityMoved();
extern __declspec(dllexport) char* GetEventRoomCreated();
extern __declspec(dllexport) char* GetEventTurnStart();
extern __declspec(dllexport) char* GetEventTurnEnd();
extern __declspec(dllexport) char* GetEventRoundStart();
extern __declspec(dllexport) char* GetEventRoundEnd();
extern __declspec(dllexport) char* GetEventStatusApplied();
extern __declspec(dllexport) char* GetEventStatusRemoved();
extern __declspec(dllexport) char* GetEventStatusCheck();

// Context Key Constants - Direct exposure of toolkit constants
extern __declspec(dllexport) char* GetContextKeyAttacker();
extern __declspec(dllexport) char* GetContextKeyTarget();
extern __declspec(dllexport) char* GetContextKeyWeapon();
extern __declspec(dllexport) char* GetContextKeyDamageType();
extern __declspec(dllexport) char* GetContextKeyAdvantage();
extern __declspec(dllexport) char* GetContextKeyRoll();
extern __declspec(dllexport) char* GetContextKeyOldPosition();
extern __declspec(dllexport) char* GetContextKeyNewPosition();
extern __declspec(dllexport) char* GetContextKeyRoomID();

// Modifier Creation Functions - Direct exposure of toolkit factories
extern __declspec(dllexport) char* CreateModifier(char* source, char* modifierType, int value, int priority);
extern __declspec(dllexport) char* CreateIntModifier(char* source, char* modifierType, int value);
extern __declspec(dllexport) char* CreateDiceModifier(char* source, char* modifierType, char* diceExpression);

// Duration Constants - Direct exposure of toolkit duration types
extern __declspec(dllexport) char* GetDurationPermanent();
extern __declspec(dllexport) char* GetDurationRounds();
extern __declspec(dllexport) char* GetDurationMinutes();
extern __declspec(dllexport) char* GetDurationHours();
extern __declspec(dllexport) char* GetDurationEncounter();
extern __declspec(dllexport) char* GetDurationConcentration();
extern __declspec(dllexport) char* GetDurationShortRest();
extern __declspec(dllexport) char* GetDurationLongRest();
extern __declspec(dllexport) char* GetDurationUntilDamaged();
extern __declspec(dllexport) char* GetDurationUntilSave();

// Memory management
extern __declspec(dllexport) void FreeEventString(char* str);
extern __declspec(dllexport) char* GetVersion();
extern __declspec(dllexport) int Initialize();
extern __declspec(dllexport) void Cleanup();
extern __declspec(dllexport) int RollDice(int sides);
extern __declspec(dllexport) float CalculateDistance(float x1, float y1, float x2, float y2);
extern __declspec(dllexport) int IsValidPosition(float gridWidth, float gridHeight, float x, float y);

#ifdef __cplusplus
}
#endif
