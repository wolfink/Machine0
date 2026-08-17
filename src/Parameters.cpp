#include "Parameters.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"
#include "juce_events/juce_events.h"
#include <cmath>

JUCE_IMPLEMENT_SINGLETON(MachZParameters);

#define ImplFloatSlider(name, full_name, default_value, ...)\
  _##name##_float = std::make_unique<juce::AudioParameterFloat>(\
    juce::ParameterID(#name), #full_name, juce::NormalisableRange<float>(__VA_ARGS__), default_value);\
  _##name##_att = std::make_unique<juce::SliderParameterAttachment>(*_##name##_float, _##name);\
  _##name.setNormalisableRange(juce::NormalisableRange<double>(__VA_ARGS__));

#define ImplIntSlider(name, full_name, default_value, ...)\
	_##name##_int = std::make_unique<juce::AudioParameterInt>(\
  	juce::ParameterID(#name), #full_name, __VA_ARGS__, default_value);\
  _##name##_att = std::make_unique<juce::SliderParameterAttachment>(*_##name##_int, _##name);\
  _##name.setNormalisableRange(juce::NormalisableRange<double>(__VA_ARGS__, 1.0));

#define ImplCombo(name, full_name, default_value, offset, ...) {\
  juce::StringArray choices __VA_ARGS__;\
    _##name##_choice = std::make_unique<juce::AudioParameterChoice>(\
    juce::ParameterID(#name), #full_name, choices, default_value);\
  _##name##_att = std::make_unique<juce::ComboBoxParameterAttachment>(*_##name##_choice, _##name);\
  _##name.addItemList(choices, offset);\
  }

MachZParameters::MachZParameters()
{
  ParameterList(ImplFloatSlider,
                ImplIntSlider,
                ImplCombo)
}

#define GetFromParam(name, thing)\
    case MachZParameter::name:\
        return getInstance()->thing;

#define GetIntValue(name,...) GetFromParam(name, _##name.getValue())
int MachZParameters::Get_int_value(const MachZParameter& parameter)
{
  switch (parameter)
  {
  ParameterList_IntSliders(GetIntValue)
  default:
    return 0;
  }
}

#define GetFloatValue(name,...) GetFromParam(name, _##name.getValue())

double MachZParameters::Get_float_value(const MachZParameter& parameter)
{
  switch (parameter)
  {
  ParameterList_FloatSliders(GetFloatValue)
  default:
    return NAN;
  }
}

#define GetSlider(name,...) GetFromParam(name, _##name)

juce::Slider& MachZParameters::Get_slider(const MachZParameter& parameter)
{
  switch (parameter)
  {
  ParameterList(GetSlider, GetSlider, Ignore)
    default:
    return getInstance()->_sld_dummy;
  }
}

#define GetChoice(name, ...) GetFromParam(name, _##name.getSelectedItemIndex())

int MachZParameters::Get_choice(const MachZParameter& parameter)
{
  switch(parameter) {
  ParameterList_ChoiceCombos(GetChoice) 
  default:
    return 0;
  }
}

#define GetCombo(name, ...) GetFromParam(name, _##name)
juce::ComboBox& MachZParameters::Get_combo_box(const MachZParameter& parameter)
{
  switch(parameter) {
    ParameterList_ChoiceCombos(GetCombo)
    default:
      return getInstance()->_cmb_dummy;
  }
}
