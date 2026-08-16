#include "GeneratorPanel.h"
#include <juce_gui_basics/juce_gui_basics.h>

GeneratorPanel::GeneratorPanel() :
  _slw1(MachZParameters::Get_slider(MachZParameter::slw1)),
  _drv1(MachZParameters::Get_slider(MachZParameter::drv1)),
  _slw2(MachZParameters::Get_slider(MachZParameter::slw2)),
  _drv2(MachZParameters::Get_slider(MachZParameter::drv2)),
  _apkt(MachZParameters::Get_slider(MachZParameter::apkt)),
  _ap1(MachZParameters::Get_slider(MachZParameter::ap1)),
  _ap2(MachZParameters::Get_slider(MachZParameter::ap2)),
  _dist1type(MachZParameters::Get_combo_box(MachZParameter::dist1type)),
  _dist2type(MachZParameters::Get_combo_box(MachZParameter::dist2type))
{
  _slw1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _slw.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _drv1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _drv.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _slw2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _slw.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _drv2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _drv.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _apkt.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _ap1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _ap.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _ap2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  // _ap2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  _dist1type.onChange = [this]() {
    resized();
  };
  _dist2type.onChange = [this]() {
    resized();
  };

  addAndMakeVisible(_slw1);
  addAndMakeVisible(_drv1);
  addAndMakeVisible(_slw2);
  addAndMakeVisible(_drv2);
  addAndMakeVisible(_apkt);
  addAndMakeVisible(_ap1);
  addAndMakeVisible(_ap2);
  addAndMakeVisible(_dist1type);
  addAndMakeVisible(_dist2type);
}

void GeneratorPanel::resized()
{
  auto bounds = getLocalBounds();

  auto dist1_section = bounds.removeFromTop(100);
  juce::FlexBox dist1_flex;
  dist1_flex.items.add(juce::FlexItem(_dist1type)
                       .withFlex(1)
                       .withMaxHeight(20));
  printf("show item %d\n", _dist1type.getSelectedItemIndex());
  _slw1.setVisible(false);
  _drv1.setVisible(false);
  if (_dist1type.getSelectedItemIndex() == 0) {
    _slw1.setVisible(true);
    dist1_flex.items.add(juce::FlexItem(_slw1)
                         .withFlex(1));
  } else {
    _drv1.setVisible(true);
    dist1_flex.items.add(juce::FlexItem(_drv1)
                         .withFlex(1));
  }
  dist1_flex.performLayout(dist1_section);

  auto allpass_section = bounds.removeFromTop(100);
  juce::FlexBox allpass;
  allpass.items.add(juce::FlexItem(_apkt)
                    .withFlex(1));
  allpass.items.add(juce::FlexItem(_ap1)
                    .withFlex(1));
  allpass.items.add(juce::FlexItem(_ap2)
                    .withFlex(1));
  allpass.performLayout(allpass_section);

  auto dist2_section = bounds.removeFromTop(100);
  juce::FlexBox dist2_flex;
  dist2_flex.items.add(juce::FlexItem(_dist2type)
                       .withFlex(1)
                       .withMaxHeight(20));
  _slw2.setVisible(false);
  _drv2.setVisible(false);
  if (_dist2type.getSelectedItemIndex() == 0) {
    _slw2.setVisible(true);
    dist2_flex.items.add(juce::FlexItem(_slw2)
                         .withFlex(1));
  } else {
    _drv2.setVisible(true);
    dist2_flex.items.add(juce::FlexItem(_drv2)
                         .withFlex(1));
  }
  dist2_flex.performLayout(dist2_section);
}
