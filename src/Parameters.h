#pragma once

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_processors_headless/juce_audio_processors_headless.h"
#include "juce_events/juce_events.h"
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

// float_slider(name, full_name, default_value, range...)
// choice_combo(name, full_name, default_value, offset, choice_array...)
#define ParameterList(float_slider, int_slider, choice_combo)\
	int_slider(osc1c, Oscillator 1 Coarse, 1, -1, 32)\
	float_slider(osc1f, Oscillator 1 Fine, 0.0, -1.0, 1.0)\
	int_slider(osc2c, Oscillator 2 Coarse, 1, -1, 32)\
	float_slider(osc2f, Oscillator 2 Fine, 0.0, -1.0, 1.0)\
	int_slider(osc3c, Oscillator 3 Coarse, 1, -1, 32)\
	float_slider(osc3f, Oscillator 3 Fine, 0.0, -1.0, 1.0)\
	int_slider(osc4c, Oscillator 4 Coarse, 1, -1, 32)\
	float_slider(osc4f, Oscillator 4 Fine, 0.0, -1.0, 1.0)\
	float_slider(osc1fm2, Oscillator 1 FM -> 2, 0.0, 0.0, 1.0)\
	float_slider(osc1fm3, Oscillator 1 FM -> 3, 0.0, 0.0, 1.0)\
	float_slider(osc1fm4, Oscillator 1 FM -> 4, 0.0, 0.0, 1.0)\
	float_slider(osc2fm3, Oscillator 2 FM -> 3, 0.0, 0.0, 1.0)\
	float_slider(osc2fm4, Oscillator 2 FM -> 4, 0.0, 0.0, 1.0)\
	float_slider(osc3fm4, Oscillator 3 FM -> 4, 0.0, 0.0, 1.0)\
	float_slider(osc1g, Oscillator 1 Gain, 0.7, 0.0, 1.0)\
	float_slider(osc2g, Oscillator 2 Gain, 0.7, 0.0, 1.0)\
	float_slider(osc3g, Oscillator 3 Gain, 0.7, 0.0, 1.0)\
	float_slider(osc4g, Oscillator 4 Gain, 0.7, 0.0, 1.0)\
  float_slider(slw1, Slew 1, 1.0, 0.0, 1.0)\
  float_slider(drv1, Drive 1, 1.0, 1.0, 10.0, 0.01, 0.5, true)\
  float_slider(apkt, Allpass Key Tracking, 0.0, 0.0, 1.0)\
  float_slider(ap1, Allpass 1, 0.0, 20.0, 10000.0, 0.01, 3, true)\
  float_slider(ap2, Allpass 2, 0.0, 20.0, 10000.0, 0.01, 3, true)\
  float_slider(slw2, Slew 2, 1.0, 0.0, 1.0)\
  float_slider(drv2, Drive 2, 1.0, 1.0, 10.0, 0.01, 0.5, true)\
  choice_combo(dist1type, Distortion Type 1, 0, 1, {"Slew", "Drive"})\
  choice_combo(dist2type, Distortion Type 2, 0, 1, {"Slew", "Drive"})\

#define ParameterList_ApplyAll(f) ParameterList(f, f, f)
#define ParameterList_FloatSliders(f) ParameterList(f, Ignore, Ignore)
#define ParameterList_IntSliders(f) ParameterList(Ignore, f, Ignore)
#define ParameterList_ChoiceCombos(f) ParameterList(Ignore, Ignore, f)

#define Ignore(...)

#define Enumerate(name, ...) name,
enum class MachZParameter 
{
  ParameterList_ApplyAll(Enumerate)
  NUM
};

#undef Enumerate



class MachZParameters
{
  #define DefineFloatSlider(name,...)\
    juce::Slider _##name;\
    std::unique_ptr<juce::SliderParameterAttachment> _##name##_att;\
    std::unique_ptr<juce::AudioParameterFloat> _##name##_float;

  #define DefineIntSlider(name,...)\
  	juce::Slider _##name;\
  	std::unique_ptr<juce::SliderParameterAttachment> _##name##_att;\
  	std::unique_ptr<juce::AudioParameterInt> _##name##_int;

  #define DefineCombo(name, ...)\
    juce::ComboBox _##name;\
    std::unique_ptr<juce::ComboBoxParameterAttachment> _##name##_att;\
    std::unique_ptr<juce::AudioParameterChoice> _##name##_choice;

  juce::Slider _sld_dummy;
  juce::ComboBox _cmb_dummy;
  ParameterList(DefineFloatSlider,
                DefineIntSlider,
                DefineCombo)

public:
  MachZParameters();

  // float slider functions
  static int Get_int_value(const MachZParameter& parameter);
  static double Get_float_value(const MachZParameter& parameter);
  static juce::Slider& Get_slider(const MachZParameter& parameter);

  // choice combo functions
  static int Get_choice(const MachZParameter& parameter);
  static juce::ComboBox& Get_combo_box(const MachZParameter& parameter);

  JUCE_DECLARE_SINGLETON(MachZParameters, true);
};
