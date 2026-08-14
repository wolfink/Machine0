#include "GeneratorPanel.h"
#include <juce_gui_basics/juce_gui_basics.h>

GeneratorPanel::GeneratorPanel() :
  _slw(MachZParameters::Get_slider(MachZParameter::slw1)),
  _drv(MachZParameters::Get_slider(MachZParameter::drv1)),
  _ap1(MachZParameters::Get_slider(MachZParameter::ap1)),
  _ap2(MachZParameters::Get_slider(MachZParameter::ap2))
{
  _slw.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _slw.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _drv.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _drv.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _ap1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _ap.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _ap2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _ap2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_slw);
  addAndMakeVisible(_drv);
  addAndMakeVisible(_ap1);
  addAndMakeVisible(_ap2);
}

void GeneratorPanel::resized()
{
  auto bounds = getLocalBounds();
  _slw.setBounds(bounds.removeFromTop(100));
  auto allpass_section = bounds.removeFromTop(100);
  _ap1.setBounds(allpass_section.removeFromLeft(200));
  _ap2.setBounds(allpass_section.removeFromLeft(200));
  _drv.setBounds(bounds.removeFromTop(100));
}
