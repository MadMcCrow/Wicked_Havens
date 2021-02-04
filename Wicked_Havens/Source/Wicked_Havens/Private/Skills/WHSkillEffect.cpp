#include "Skills/WHSkillEffect.h"

FWHAttributes UWHSkillEffect::GetResult_Implementation(const FWHAttributes &Attributes, int32 level)
{
    return Attributes;
}


FWHAttributes UWHSkillEffect::ChangeValue(const FWHAttributes &Attributes, EWHAttributeTypes Type, const FVariant& NewValue )
{
	FVariant Base;
    auto Map = Attributes.GetMap();
    if (FWHAttribute *Found = Map.Find(Type))
    {
        Base = Found->BaseValue;
    }
    else
    {
        Base = NewValue;
    }

    Map.Add(Type,FWHAttribute(Base, NewValue));
    return FWHAttributes(Map);
}


FWHAttributes UWHSkillEffect::ChangeBaseValue(const FWHAttributes &Attributes, EWHAttributeTypes Type, const FVariant& NewBaseValue )
{
    FVariant Value;
    auto Map = Attributes.GetMap();
    if (FWHAttribute* Found = Map.Find(Type))
    {
        Value = Found->Value;
    }
    else
    {
        Value = NewBaseValue;
    }

    Map.Add(Type,FWHAttribute(NewBaseValue, Value));
    return FWHAttributes(Map);
}