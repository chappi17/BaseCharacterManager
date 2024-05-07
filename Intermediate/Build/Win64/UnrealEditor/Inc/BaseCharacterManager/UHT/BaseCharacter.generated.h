// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BaseCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef BASECHARACTERMANAGER_BaseCharacter_generated_h
#error "BaseCharacter.generated.h already included, missing '#pragma once' in BaseCharacter.h"
#endif
#define BASECHARACTERMANAGER_BaseCharacter_generated_h

#define FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execChangeToTPView); \
	DECLARE_FUNCTION(execChangeToFPView); \
	DECLARE_FUNCTION(execChangeView);


#define FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABaseCharacter(); \
	friend struct Z_Construct_UClass_ABaseCharacter_Statics; \
public: \
	DECLARE_CLASS(ABaseCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BaseCharacterManager"), NO_API) \
	DECLARE_SERIALIZER(ABaseCharacter)


#define FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ABaseCharacter(ABaseCharacter&&); \
	ABaseCharacter(const ABaseCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABaseCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABaseCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABaseCharacter) \
	NO_API virtual ~ABaseCharacter();


#define FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_24_PROLOG
#define FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_INCLASS_NO_PURE_DECLS \
	FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BASECHARACTERMANAGER_API UClass* StaticClass<class ABaseCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Test5_4_Plugins_BaseCharacterManager_Source_BaseCharacterManager_Public_BaseCharacter_h


#define FOREACH_ENUM_ECAMERAVIEWPOINTS(op) \
	op(ECameraViewPoints::FP) \
	op(ECameraViewPoints::TP) 

enum class ECameraViewPoints : uint8;
template<> struct TIsUEnumClass<ECameraViewPoints> { enum { Value = true }; };
template<> BASECHARACTERMANAGER_API UEnum* StaticEnum<ECameraViewPoints>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
