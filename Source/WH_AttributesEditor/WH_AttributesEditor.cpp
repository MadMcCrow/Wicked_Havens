/* Copyright © Noé Perard-Gayot 2022. */

#include "WH_AttributesEditor.h"

#include "WHAttributeCustomization.h"
#include "Modules/ModuleManager.h"
#include "WHAttributeNameCustomization.h"
#include "WHAttributeNamePin.h"
#include "WHAttributeTypeCustomization.h"

IMPLEMENT_MODULE(FWH_AttributesEditor, WH_AttributesEditor);

void FWH_AttributesEditor::StartupModule()
{
	// Get property editor module
	//auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// register WHAttributeName property editor
	//PropertyModule.RegisterCustomPropertyTypeLayout("WHAttributeName", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWHAttributeNameCustomization::MakeInstance));

	// register WHAttributeType property editor
	//PropertyModule.RegisterCustomPropertyTypeLayout("WHAttributeType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWHAttributeTypeCustomization::MakeInstance));

	// WHAttribute property editor
	//PropertyModule.RegisterCustomPropertyTypeLayout("WHAttribute", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWHAttributeCustomization::MakeInstance));

	//WHAttributeName Pin factory
	//WHAttributeNamePinFactory = MakeShareable(new FWHAttributeNamePinFactory());
	//FEdGraphUtilities::RegisterVisualPinFactory(WHAttributeNamePinFactory);


}

void FWH_AttributesEditor::ShutdownModule()
{
	// Get property editor module :
	//auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// unregister WHAttributeName custom editor layout
	//PropertyModule.UnregisterCustomPropertyTypeLayout("WHAttributeName");

	// unregister WHAttributeType property editor
	//PropertyModule.UnregisterCustomPropertyTypeLayout("WHAttributeType");

	// unregister WHAttribute custom editor layout
	//PropertyModule.UnregisterCustomPropertyTypeLayout("WHAttribute");

	// Unregister WHAttributeName custom pin factory
	//FEdGraphUtilities::UnregisterVisualPinFactory(WHAttributeNamePinFactory);

}
