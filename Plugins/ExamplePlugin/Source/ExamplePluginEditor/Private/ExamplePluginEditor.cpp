#include "ExamplePluginEditor.h"

#define LOCTEXT_NAMESPACE "FExamplePluginEditorModule"

void FExamplePluginEditorModule::StartupModule() {}

void FExamplePluginEditorModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FExamplePluginEditorModule, ExamplePluginEditor)