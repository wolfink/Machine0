#include "GeneratorPanel.h"
#include <juce_gui_basics/juce_gui_basics.h>

GeneratorPanel::GeneratorPanel() :
  _slw1(MachZParameters::Get_slider(MachZParameter::slw1)),
  _drv1(MachZParameters::Get_slider(MachZParameter::drv1))
{
  _slw1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _slw1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _drv1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _drv1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_slw1);
  addAndMakeVisible(_drv1);
}

void GeneratorPanel::resized()
{
  auto bounds = getLocalBounds();
  _slw1.setBounds(bounds.removeFromLeft(200));
  _drv1.setBounds(bounds.removeFromLeft(200));
}
