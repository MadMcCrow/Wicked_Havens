/* Copyright © Noé Perard-Gayot 2022. */

#include "WH_AttributesEditor.h"
#include "Modules/ModuleManager.h"
#include "WHAttributeRefPin.h"
#include "WHAttributeRefCustomization.h"

IMPLEMENT_MODULE(FWH_AttributesEditor, WH_AttributesEditor);

void FWH_AttributesEditor::StartupModule()
{
	// Get property editor module
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// register WHAttributeRef property editor
	PropertyModule.RegisterCustomPropertyTypeLayout("WHAttributeRef", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWHAttributeRefCustomization::MakeInstance));
	// WHAttributeRef Pin factory
	WHAttributeRefPinFactory = MakeShareable(new FWHAttributeRefPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(WHAttributeRefPinFactory);
}

void FWH_AttributesEditor::ShutdownModule()
{
	// Get property editor module :
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// unregister WHAttributeName custom editor layout
	PropertyModule.UnregisterCustomPropertyTypeLayout("WHAttributeRef");
	// Unregister WHAttributeName custom pin factory
	FEdGraphUtilities::UnregisterVisualPinFactory(WHAttributeRefPinFactory);
	WHAttributeRefPinFactory.Reset();
}
