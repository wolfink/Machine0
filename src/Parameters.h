#pragma once

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_processors_headless/juce_audio_processors_headless.h"
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#define mzparams MachZParameters::getInstance()

class MachZParameters 
{
public:
    juce::Slider Slew;
    std::unique_ptr<juce::SliderParameterAttachment> SlewParameterAttachment;
    std::unique_ptr<juce::AudioParameterFloat> SlewParameter;

    MachZParameters();
    JUCE_DECLARE_SINGLETON(MachZParameters, true);
};
