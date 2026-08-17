#include "OscPanel.h"
#include "../Parameters.h"

OscPanel::OscPanel() :
  osc1c(MachZParameters::Get_slider(MachZParameter::osc1c)),
  osc1f(MachZParameters::Get_slider(MachZParameter::osc1f)),
  osc2c(MachZParameters::Get_slider(MachZParameter::osc2c)),
  osc2f(MachZParameters::Get_slider(MachZParameter::osc2f)),
  osc3c(MachZParameters::Get_slider(MachZParameter::osc3c)),
  osc3f(MachZParameters::Get_slider(MachZParameter::osc3f)),
  osc4c(MachZParameters::Get_slider(MachZParameter::osc4c)),
  osc4f(MachZParameters::Get_slider(MachZParameter::osc4f)),
  osc1fm2(MachZParameters::Get_slider(MachZParameter::osc1fm2)),
  osc1fm3(MachZParameters::Get_slider(MachZParameter::osc1fm3)),
  osc1fm4(MachZParameters::Get_slider(MachZParameter::osc1fm4)),
  osc2fm3(MachZParameters::Get_slider(MachZParameter::osc2fm3)),
  osc2fm4(MachZParameters::Get_slider(MachZParameter::osc2fm4)),
  osc3fm4(MachZParameters::Get_slider(MachZParameter::osc3fm4)),
  osc1g(MachZParameters::Get_slider(MachZParameter::osc1g)),
  osc2g(MachZParameters::Get_slider(MachZParameter::osc2g)),
  osc3g(MachZParameters::Get_slider(MachZParameter::osc3g)),
  osc4g(MachZParameters::Get_slider(MachZParameter::osc4g))
{
  osc1c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm3.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2fm3.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1g.setValue(1.0);
  osc2g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2g.setValue(0.0);
  osc3g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3g.setValue(0.0);
  osc4g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4g.setValue(0.0);

  addAndMakeVisible(osc1c);
  addAndMakeVisible(osc1f);
  addAndMakeVisible(osc2c);
  addAndMakeVisible(osc2f);
  addAndMakeVisible(osc3c);
  addAndMakeVisible(osc3f);
  addAndMakeVisible(osc4c);
  addAndMakeVisible(osc4f);
  addAndMakeVisible(osc1fm2);
  addAndMakeVisible(osc1fm3);
  addAndMakeVisible(osc1fm4);
  addAndMakeVisible(osc2fm3);
  addAndMakeVisible(osc2fm4);
  addAndMakeVisible(osc3fm4);
  addAndMakeVisible(osc1g);
  addAndMakeVisible(osc2g);
  addAndMakeVisible(osc3g);
  addAndMakeVisible(osc4g);
}

void OscPanel::resized()
{
  auto bounds = getLocalBounds();
  auto knob_size = 200;


  // Osc pitch controls
  auto osc_pitch_section = bounds.removeFromLeft(300);

  juce::FlexBox osc_pitch_section_flx;
  osc_pitch_section_flx.flexDirection = juce::FlexBox::Direction::column;

  juce::FlexBox osc1_flx;
  osc1_flx.items.add(juce::FlexItem(osc1c).withFlex(1));
  osc1_flx.items.add(juce::FlexItem(osc1f).withFlex(1));

  juce::FlexBox osc2_flx;
  osc2_flx.items.add(juce::FlexItem(osc2c).withFlex(1));
  osc2_flx.items.add(juce::FlexItem(osc2f).withFlex(1));

  juce::FlexBox osc3_flx;
  osc3_flx.items.add(juce::FlexItem(osc3c).withFlex(1));
  osc3_flx.items.add(juce::FlexItem(osc3f).withFlex(1));

  juce::FlexBox osc4_flx;
  osc4_flx.items.add(juce::FlexItem(osc4c).withFlex(1));
  osc4_flx.items.add(juce::FlexItem(osc4f).withFlex(1));

  osc_pitch_section_flx.items.add(juce::FlexItem(osc1_flx).withHeight(100));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc2_flx).withHeight(100));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc3_flx).withHeight(100));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc4_flx).withHeight(100));

  osc_pitch_section_flx.performLayout(osc_pitch_section);


  // Osc FM controls
  auto osc_fm_section = bounds.removeFromLeft(450);

  juce::FlexBox osc_fm_section_flx;
  osc_fm_section_flx.flexDirection = juce::FlexBox::Direction::column;

  juce::FlexBox osc1_fm_flx;
  osc1_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm2)
                        .withHeight(100)
                        .withWidth(150));
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm3)
                        .withHeight(100)
                        .withWidth(150));
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm4)
                        .withHeight(100)
                        .withWidth(150));

  juce::FlexBox osc2_fm_flx;
  osc2_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc2_fm_flx.items.add(juce::FlexItem(osc2fm3)
                        .withHeight(100)
                        .withWidth(150));
  osc2_fm_flx.items.add(juce::FlexItem(osc2fm4)
                        .withHeight(100)
                        .withWidth(150));

  juce::FlexBox osc3_fm_flx;
  osc3_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc3_fm_flx.items.add(juce::FlexItem(osc3fm4)
                        .withHeight(100)
                        .withWidth(150));

  osc_fm_section_flx.items.add(juce::FlexItem(osc1_fm_flx).withHeight(100));
  osc_fm_section_flx.items.add(juce::FlexItem(osc2_fm_flx).withHeight(100));
  osc_fm_section_flx.items.add(juce::FlexItem(osc3_fm_flx).withHeight(100));
  osc_fm_section_flx.performLayout(osc_fm_section);

  auto osc_gain_section = bounds.removeFromLeft(150);
  juce::FlexBox osc_gain_section_flx;
  osc_gain_section_flx.flexDirection = juce::FlexBox::Direction::column;
  osc_gain_section_flx.items.add(juce::FlexItem(osc1g).withFlex(1));
  osc_gain_section_flx.items.add(juce::FlexItem(osc2g).withFlex(1));
  osc_gain_section_flx.items.add(juce::FlexItem(osc3g).withFlex(1));
  osc_gain_section_flx.items.add(juce::FlexItem(osc4g).withFlex(1));
  osc_gain_section_flx.performLayout(osc_gain_section);
}
