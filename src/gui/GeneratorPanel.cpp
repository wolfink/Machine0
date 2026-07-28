#include "GeneratorPanel.h"
#include <juce_gui_basics/juce_gui_basics.h>

GeneratorPanel::GeneratorPanel() :
    _slew(mzparams->Slew)
{
    _slew.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    _slew.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
    addAndMakeVisible(_slew);
}

void GeneratorPanel::resized()
{
    _slew.setBounds(getLocalBounds());
}
