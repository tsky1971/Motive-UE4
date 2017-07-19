// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class NatNet : ModuleRules
{
    public NatNet(TargetInfo Target)
    {
        Type = ModuleType.External;

        string includePath = Path.Combine(ModuleDirectory, "include");
        PublicIncludePaths.AddRange(new string[] { includePath });

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library
            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib", "x64"));
            //PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib", "x86"));
            PublicAdditionalLibraries.Add("NatNetLib.lib");

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("NatNetLib.dll");
			
            RuntimeDependencies.Add(new RuntimeDependency("NatNetLib.dll"));
        }
    }
}
