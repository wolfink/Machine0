#pragma once

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Parameters.h"
#include "juce_events/juce_events.h"

class GeneratorPanel : public juce::Component
{
    juce::Slider& _slw1;
    juce::Slider& _drv1;
    juce::Slider& _slw2;
    juce::Slider& _drv2;
    juce::Slider& _ap1;
    juce::Slider& _ap2;
    juce::ComboBox& _dist1type;
    juce::ComboBox& _dist2type;

public:
    GeneratorPanel();
    virtual void resized() override;
};
