using UnrealBuildTool;

public class ExamplePluginEditor : ModuleRules
{
    public ExamplePluginEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "AssetTools",
                "MainFrame",
            });

        PrivateIncludePaths.AddRange(
            new string[] {
                "ExamplePluginEditor/Private",
                "ExamplePluginEditor/Private/Factories",
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "ExamplePlugin",
                "UnrealEd",
                "protobuf"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "AssetTools",
                "UnrealEd",
            });
    }
}