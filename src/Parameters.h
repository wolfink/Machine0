#pragma once

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_processors_headless/juce_audio_processors_headless.h"
#include "juce_events/juce_events.h"
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

// P(name, full_name, default_value, range...)
#define ParameterList(float_slider)\
	float_slider(slw1, Slew 1, 1.0, 0.0, 1.0)\
	float_slider(drv1, Drive 1, 1.0, 1.0, 10.0, 0.01, 0.5, true)\
	float_slider(ap1, Allpass 1, 0.0, 20.0, 10000.0, 0.01, 3, true)\
	float_slider(ap2, Allpass 2, 0.0, 20.0, 10000.0, 0.01, 3, true)

#define Enumerate(name, ...) name,

#define DefineSlider(name,...)\
	juce::Slider _##name;\
  std::unique_ptr<juce::SliderParameterAttachment> _##name##ParameterAttachment;\
  std::unique_ptr<juce::AudioParameterFloat> _##name##Parameter;

#define AttachSlider(name, full_name, default_value, ...)\
    _##name##Parameter = std::make_unique<juce::AudioParameterFloat>(\
        juce::ParameterID(#name), #full_name, juce::NormalisableRange<float>(__VA_ARGS__), default_value);\
    _##name##ParameterAttachment = std::make_unique<juce::SliderParameterAttachment>(*_##name##Parameter, _##name);\
    _##name.setNormalisableRange(juce::NormalisableRange<double>(__VA_ARGS__));

#define GetFloatValue(name,...)\
	case MachZParameter::name:\
		return getInstance()->_##name.getValue();

#define GetSlider(name,...)\
	case MachZParameter::name:\
		return getInstance()->_##name;


enum class MachZParameter 
{
  ParameterList(Enumerate)
  NUM
};
#undef Enumerate

class MachZParameters
{
  juce::Slider _sld_dummy;
  ParameterList(DefineSlider)

public:
  MachZParameters();
  static double Get_float_value(const MachZParameter& parameter);
  static juce::Slider& Get_slider(const MachZParameter& parameter);

  JUCE_DECLARE_SINGLETON(MachZParameters, true);
};
