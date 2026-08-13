#pragma once

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_processors_headless/juce_audio_processors_headless.h"
#include "juce_events/juce_events.h"
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#define ParameterList(P)\
	P(slw1, Slew 1, 1.0, 0.0, 1.0)\
	P(drv1, Drive 1, 1.0, 1.0, 10.0, 0.01, 0.5, true)\

#define Enumerate(name, ...) name,

#define Define(name,...)\
	juce::Slider _##name;\
  std::unique_ptr<juce::SliderParameterAttachment> _##name##ParameterAttachment;\
  std::unique_ptr<juce::AudioParameterFloat> _##name##Parameter;

#define Attach(name, full_name, dft, ...)\
    _##name##Parameter = std::make_unique<juce::AudioParameterFloat>(\
        juce::ParameterID(#name), #full_name, juce::NormalisableRange<float>(__VA_ARGS__), dft);\
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
  ParameterList(Define)

public:
  MachZParameters();
  static double Get_float_value(const MachZParameter& parameter);
  static juce::Slider& Get_slider(const MachZParameter& parameter);

  JUCE_DECLARE_SINGLETON(MachZParameters, true);
};
