 /* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeValueWidget.h"
#include "DetailLayoutBuilder.h"
#include "SEnumCombo.h"
#include "SSearchableComboBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Colors/SColorPicker.h"

#define LOCTEXT_NAMESPACE "SWHAttributeValueWidget"



void SWHAttributeValueWidget::Construct(const FArguments& InArgs)
{
	EditedAttributeValue = InArgs._AtributeValue;
	EditedAttributeType  = InArgs._AttributeType;
	OnTypeSelectionChange = InArgs._OnTypeSelectionChange;

	bool bTypePicker = InArgs._bShowTypeSelector.Get();
	UEnum* Enum = StaticEnum<EWHAttributeTypes>();

	// Add selection box
	AddSlot()
	.AutoHeight()
	[
		SNew(SEnumComboBox, Enum)
		.OnEnumSelectionChanged(this, &SWHAttributeValueWidget::OnEnumSelectionChanged)
		.Visibility(bTypePicker ? EVisibility::Visible: EVisibility::Collapsed)
		.Font(IDetailLayoutBuilder::GetDetailFont())
	];
	// Add GUID text box
	AddSlot()
	.AutoHeight()
	[
		MakeValueEntryWidget()
	];
}

 void SWHAttributeValueWidget::CommitValue()
 {
	OnTypeSelectionChange.ExecuteIfBound(MakeShared<FWHAttributeValue>(EditedAttributeValue.Get()));
 }


 void SWHAttributeValueWidget::OnEnumSelectionChanged(int32 NewEnumValue, ESelectInfo::Type InArg)
{
	const EWHAttributeTypes AttributeType = static_cast<EWHAttributeTypes>(NewEnumValue);
	EditedAttributeType.Set(AttributeType);
}


 void SWHAttributeValueWidget::OnTextValueInputChanged(const FText& TextCommitted, ETextCommit::Type InArg)
 {
	switch(EditedAttributeType.Get())
	{
	case EWHAttributeTypes::TName :
		EditedAttributeValue =  FName(TextCommitted.ToString());
		return;
	case EWHAttributeTypes::TString :
		EditedAttributeValue =  TextCommitted.ToString();
		return;
	case EWHAttributeTypes::TText :
		EditedAttributeValue =  TextCommitted;
		return;
	default:
			break;
	}
 }


TSharedRef<SWidget> SWHAttributeValueWidget::MakeValueEntryWidget()
{
	switch (EditedAttributeType.Get())
	{
	case EWHAttributeTypes::TBool:
		 return SNew(SCheckBox)
		.OnCheckStateChanged(this,&SWHAttributeValueWidget::OnBoolValueChanged)
		.IsEnabled(true)
		.IsChecked(bool(EditedAttributeValue.Get()) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	case EWHAttributeTypes::TInt:
		return	SNew(SNumericEntryBox<int32>)
		.OnValueCommitted(this, &SWHAttributeValueWidget::OnNumericValueInputChanged);
	case EWHAttributeTypes::TInt64:
		return	SNew(SNumericEntryBox<int64>)
		.OnValueCommitted(this, &SWHAttributeValueWidget::OnNumericValueInputChanged);
	case EWHAttributeTypes::TFloat:
		return	SNew(SNumericEntryBox<float>)
		.OnValueCommitted(this, &SWHAttributeValueWidget::OnNumericValueInputChanged);
	case EWHAttributeTypes::TByte:
		return	SNew(SNumericEntryBox<uint8>)
		.OnValueCommitted(this, &SWHAttributeValueWidget::OnNumericValueInputChanged);
	case EWHAttributeTypes::TEnum:
		UEnum* EnumClass;
		return	SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(.3f)
		.VAlign(VAlign_Center)
		[
			SNullWidget::NullWidget // TODO : Add a picker for Enum
		]
		+SHorizontalBox::Slot()
		.FillWidth(.7f)
		.VAlign(VAlign_Center)
		[
			SNew(SEnumComboBox, EnumClass)
		];
	case EWHAttributeTypes::TText:
	case EWHAttributeTypes::TString:
	case EWHAttributeTypes::TName:
		return	SNew(SEditableText)
		.OnTextCommitted(this, &SWHAttributeValueWidget::OnTextValueInputChanged);
	case EWHAttributeTypes::TVector:
		return SNew(SNumericVectorInputBox<float>);
	case EWHAttributeTypes::TRotator:
		return SNew(SNumericVectorInputBox<float>);
	case EWHAttributeTypes::TColor:
		return SNew(SColorPicker).OnColorCommitted(this, &SWHAttributeValueWidget::OnColorCommitted);
	case EWHAttributeTypes::TTransform:
	case EWHAttributeTypes::TArray:
	case EWHAttributeTypes::TObject:
	case EWHAttributeTypes::TError:
	case EWHAttributeTypes::TMultiple:
	default: ;
		return SNullWidget::NullWidget;
	}
}


#undef LOCTEXT_NAMESPACE
