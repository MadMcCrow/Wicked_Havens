/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeCustomization.h"
#include "PropertyCustomizationHelpers.h"
#include "PropertyHandle.h"
#include "WHAttributeNameWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "WHAttributeValueWidget.h"


#define LOCTEXT_NAMESPACE "WHAttributeContainerCustomization"


void FWHAttributeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                    FDetailWidgetRow& HeaderRow,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	AttributePropertyHandle = InStructPropertyHandle;
	auto EmptyString =  FName(NAME_None).ToString();
	// Set widget :
	HeaderRow
		.NameContent()
		[
			InStructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(250.0f)
		.MaxDesiredWidth(0.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(2.0f, 2.0f, 2.0f, 2.0f)
			.AutoWidth()
			[
				SNew(SWHAttributeNameWidget)
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(2.0f, 2.0f, 2.0f, 2.0f)
			.AutoWidth()
			[
				SNew(SWHAttributeValueWidget)
			]
		];
	// This avoids making duplicate reset boxes
	AttributePropertyHandle->MarkResetToDefaultCustomized();
}

void FWHAttributeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle,
                                                      IDetailChildrenBuilder& StructBuilder,
                                                      IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}


#undef LOCTEXT_NAMESPACE
