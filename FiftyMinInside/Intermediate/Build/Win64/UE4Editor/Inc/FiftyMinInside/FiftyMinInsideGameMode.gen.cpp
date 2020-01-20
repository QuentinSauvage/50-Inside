// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FiftyMinInside/FiftyMinInsideGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFiftyMinInsideGameMode() {}
// Cross Module References
	FIFTYMININSIDE_API UClass* Z_Construct_UClass_AFiftyMinInsideGameMode_NoRegister();
	FIFTYMININSIDE_API UClass* Z_Construct_UClass_AFiftyMinInsideGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_FiftyMinInside();
// End Cross Module References
	void AFiftyMinInsideGameMode::StaticRegisterNativesAFiftyMinInsideGameMode()
	{
	}
	UClass* Z_Construct_UClass_AFiftyMinInsideGameMode_NoRegister()
	{
		return AFiftyMinInsideGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AFiftyMinInsideGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_FiftyMinInside,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "FiftyMinInsideGameMode.h" },
		{ "ModuleRelativePath", "FiftyMinInsideGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFiftyMinInsideGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::ClassParams = {
		&AFiftyMinInsideGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFiftyMinInsideGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFiftyMinInsideGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFiftyMinInsideGameMode, 2601449137);
	template<> FIFTYMININSIDE_API UClass* StaticClass<AFiftyMinInsideGameMode>()
	{
		return AFiftyMinInsideGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFiftyMinInsideGameMode(Z_Construct_UClass_AFiftyMinInsideGameMode, &AFiftyMinInsideGameMode::StaticClass, TEXT("/Script/FiftyMinInside"), TEXT("AFiftyMinInsideGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFiftyMinInsideGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
