// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FiftyMinInside/FiftyMinInsidePawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFiftyMinInsidePawn() {}
// Cross Module References
	FIFTYMININSIDE_API UClass* Z_Construct_UClass_AFiftyMinInsidePawn_NoRegister();
	FIFTYMININSIDE_API UClass* Z_Construct_UClass_AFiftyMinInsidePawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_FiftyMinInside();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void AFiftyMinInsidePawn::StaticRegisterNativesAFiftyMinInsidePawn()
	{
	}
	UClass* Z_Construct_UClass_AFiftyMinInsidePawn_NoRegister()
	{
		return AFiftyMinInsidePawn::StaticClass();
	}
	struct Z_Construct_UClass_AFiftyMinInsidePawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MinSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TurnSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TurnSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Acceleration_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Acceleration;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Camera;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlaneMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PlaneMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFiftyMinInsidePawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_FiftyMinInside,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "FiftyMinInsidePawn.h" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MinSpeed_MetaData[] = {
		{ "Category", "Yaw" },
		{ "Comment", "/** Min forward speed */" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "Min forward speed" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MinSpeed = { "MinSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, MinSpeed), METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MinSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MinSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MaxSpeed_MetaData[] = {
		{ "Category", "Pitch" },
		{ "Comment", "/** Max forward speed */" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "Max forward speed" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MaxSpeed = { "MaxSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, MaxSpeed), METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MaxSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MaxSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_TurnSpeed_MetaData[] = {
		{ "Category", "Plane" },
		{ "Comment", "/** How quickly pawn can steer */" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "How quickly pawn can steer" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_TurnSpeed = { "TurnSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, TurnSpeed), METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_TurnSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_TurnSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Acceleration_MetaData[] = {
		{ "Category", "Plane" },
		{ "Comment", "/** How quickly forward speed changes */" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "How quickly forward speed changes" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Acceleration = { "Acceleration", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, Acceleration), METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Acceleration_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Acceleration_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Camera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Camera component that will be our viewpoint */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "Camera component that will be our viewpoint" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00400000000b001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Camera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Camera_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_SpringArm_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Spring arm that will offset the camera */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "Spring arm that will offset the camera" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00400000000b001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_SpringArm_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_SpringArm_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_PlaneMesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Mesh" },
		{ "Comment", "/** StaticMesh component that will be the visuals for our flying pawn */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FiftyMinInsidePawn.h" },
		{ "ToolTip", "StaticMesh component that will be the visuals for our flying pawn" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_PlaneMesh = { "PlaneMesh", nullptr, (EPropertyFlags)0x00400000000b001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFiftyMinInsidePawn, PlaneMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_PlaneMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_PlaneMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFiftyMinInsidePawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MinSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_MaxSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_TurnSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Acceleration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_Camera,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_SpringArm,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFiftyMinInsidePawn_Statics::NewProp_PlaneMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFiftyMinInsidePawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFiftyMinInsidePawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFiftyMinInsidePawn_Statics::ClassParams = {
		&AFiftyMinInsidePawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AFiftyMinInsidePawn_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFiftyMinInsidePawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFiftyMinInsidePawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFiftyMinInsidePawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFiftyMinInsidePawn, 772781182);
	template<> FIFTYMININSIDE_API UClass* StaticClass<AFiftyMinInsidePawn>()
	{
		return AFiftyMinInsidePawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFiftyMinInsidePawn(Z_Construct_UClass_AFiftyMinInsidePawn, &AFiftyMinInsidePawn::StaticClass, TEXT("/Script/FiftyMinInside"), TEXT("AFiftyMinInsidePawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFiftyMinInsidePawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
