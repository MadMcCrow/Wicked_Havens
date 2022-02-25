/* Copyright © Noé Perard-Gayot 2022. */

#include "WH_AttributesEditor.h"
#include "Modules/ModuleManager.h"
#include "WHAttributeNameCustomization.h"
#include "WHAttributeNamePin.h"

IMPLEMENT_MODULE(FWH_AttributesEditor, WH_AttributesEditor);

void FWH_AttributesEditor::StartupModule()
{
	// register WHAttributeName property editor
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("WHAttributeName", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWHAttributeNameCustomization::MakeInstance));

	//WHAttributeName Pin factory
	WHAttributeNamePinFactory = MakeShareable(new FWHAttributeNamePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(WHAttributeNamePinFactory);

}

void FWH_AttributesEditor::ShutdownModule()
{
	// unregister SoftItemPath custom editor layout
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("WHAttributeName");
	FEdGraphUtilities::UnregisterVisualPinFactory(WHAttributeNamePinFactory);
}
