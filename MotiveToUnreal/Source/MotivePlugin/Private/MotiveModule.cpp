// Some copyright should be here...

#include "MotivePluginPrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

DEFINE_LOG_CATEGORY(MotiveLog);

#define LOCTEXT_NAMESPACE "FMotiveModule"



bool FMotiveModule::SearchForDllPath(const FString _searchBase, const FString _dllName)
{
	//Search Plugins folder for an instance of Dll.dll, and add to platform search path
	TArray<FString> directoriesToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
	PlatformFile.IterateDirectory(*_searchBase, Visitor);

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString file = TimestampIt.Key();
		const FString filePath = FPaths::GetPath(file);
		const FString fileName = FPaths::GetCleanFilename(file);
		if (fileName.Compare(_dllName) == 0)
		{
			FPlatformProcess::AddDllDirectory(*filePath); // only load dll when needed for use. Broken with 4.11.
			FPlatformProcess::GetDllHandle(*file); // auto-load dll with plugin - needed as 4.11 breaks above line.
			return true;
		}
	}
	return false;
}


void FMotiveModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(MotiveLog, Warning, TEXT("Motive Module Startup"));

	//// Get the base directory of this plugin
	//FString BaseDir = IPluginManager::Get().FindPlugin("MotivePlugin")->GetBaseDir();


	//FString dllName = "NatNetLib.dll";
	//if (SearchForDllPath(FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/NetNet/lib/x64/")), dllName))
	//{
	//	UE_LOG(LogInit, Log, TEXT("SearchForDllPath NatNetLib SUCCESSFUL"));
	//}
	//else
	//{
	//	//Stop loading - plugin required DLL to load successfully
	//	checkf(false, TEXT("Failed to load NatNetLib"));
	//}
}

void FMotiveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(MotiveLog, Warning, TEXT("Motive Module Shutdown"));
}


	
IMPLEMENT_MODULE(FMotiveModule, MotivePlugin)

#undef LOCTEXT_NAMESPACE