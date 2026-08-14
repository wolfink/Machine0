#pragma once

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Parameters.h"
#include "juce_events/juce_events.h"

class GeneratorPanel : public juce::Component
{
    juce::Slider& _slw;
    juce::Slider& _drv;
    juce::Slider& _ap1;
    juce::Slider& _ap2;

public:
    GeneratorPanel();
    virtual void resized() override;
};
