#include "OscPanel.h"
#include "../Parameters.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace mz
{

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
  lbl_coarse.setFont(juce::Font(16.0f, juce::Font::bold));
  lbl_coarse.setText("Coarse", juce::NotificationType::dontSendNotification);
  lbl_coarse.setColour(juce::Label::textColourId, juce::Colours::linen);
  lbl_coarse.setJustificationType(juce::Justification::left);
  addAndMakeVisible(lbl_coarse);

  lbl_fine.setFont(juce::Font(16.0f, juce::Font::bold));
  lbl_fine.setText("Fine", juce::NotificationType::dontSendNotification);
  lbl_fine.setColour(juce::Label::textColourId, juce::Colours::linen);
  lbl_fine.setJustificationType(juce::Justification::left);
  addAndMakeVisible(lbl_fine);

  osc1c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1c.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 20);
  addAndMakeVisible(osc1c);

  osc1f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1f.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  addAndMakeVisible(osc1f);

  l_osc1.setFont(juce::Font(16.0f, juce::Font::bold));
  l_osc1.setText("1", juce::NotificationType::dontSendNotification);
  l_osc1.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_osc1.setJustificationType(juce::Justification::right);
  addAndMakeVisible(l_osc1);

  osc2c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2c.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 20);
  addAndMakeVisible(osc2c);

  osc2f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2f.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  addAndMakeVisible(osc2f);

  l_osc2.setFont(juce::Font(16.0f, juce::Font::bold));
  l_osc2.setText("2", juce::NotificationType::dontSendNotification);
  l_osc2.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_osc2.setJustificationType(juce::Justification::right);
  addAndMakeVisible(l_osc2);

  osc3c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3c.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 20);
  addAndMakeVisible(osc3c);

  osc3f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3f.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  addAndMakeVisible(osc3f);

  l_osc3.setFont(juce::Font(16.0f, juce::Font::bold));
  l_osc3.setText("3", juce::NotificationType::dontSendNotification);
  l_osc3.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_osc3.setJustificationType(juce::Justification::right);
  addAndMakeVisible(l_osc3);

  osc4c.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4c.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 20);
  addAndMakeVisible(osc4c);

  osc4f.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4f.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 20);
  addAndMakeVisible(osc4f);

  l_osc4.setFont(juce::Font(16.0f, juce::Font::bold));
  l_osc4.setText("4", juce::NotificationType::dontSendNotification);
  l_osc4.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_osc4.setJustificationType(juce::Justification::right);
  addAndMakeVisible(l_osc4);

  lbl_fm.setFont(juce::Font(16.0f, juce::Font::bold));
  lbl_fm.setText("FM", juce::NotificationType::dontSendNotification);
  lbl_fm.setColour(juce::Label::textColourId, juce::Colours::linen);
  lbl_fm.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(lbl_fm);

  l_oscfm2.setFont(juce::Font(16.0f, juce::Font::bold));
  l_oscfm2.setText(u8"\u2192 2", juce::NotificationType::dontSendNotification);
  l_oscfm2.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_oscfm2.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(l_oscfm2);

  l_oscfm3.setFont(juce::Font(16.0f, juce::Font::bold));
  l_oscfm3.setText(u8"\u2192 3", juce::NotificationType::dontSendNotification);
  l_oscfm3.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_oscfm3.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(l_oscfm3);

  l_oscfm4.setFont(juce::Font(16.0f, juce::Font::bold));
  l_oscfm4.setText(u8"\u2192 4", juce::NotificationType::dontSendNotification);
  l_oscfm4.setColour(juce::Label::textColourId, juce::Colours::linen);
  l_oscfm4.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(l_oscfm4);


  osc1fm2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc1fm2);


  osc1fm3.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm3.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc1fm3);

  osc1fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1fm4.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc1fm4);

  osc2fm3.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2fm3.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc2fm3);

  osc2fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2fm4.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc2fm4);

  osc3fm4.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3fm4.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(osc3fm4);

  lbl_gain.setFont(juce::Font(16.0f, juce::Font::bold));
  lbl_gain.setText(u8"\u2192 D", juce::NotificationType::dontSendNotification);
  lbl_gain.setColour(juce::Label::textColourId, juce::Colours::linen);
  lbl_gain.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(lbl_gain);

  osc1g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc1g.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  osc1g.setValue(1.0);
  addAndMakeVisible(osc1g);

  osc2g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc2g.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  osc2g.setValue(0.0);
  addAndMakeVisible(osc2g);

  osc3g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc3g.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  osc3g.setValue(0.0);
  addAndMakeVisible(osc3g);

  osc4g.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  osc4g.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
  osc4g.setValue(0.0);
  addAndMakeVisible(osc4g);
}

void OscPanel::resized()
{
  auto bounds = getLocalBounds();
  auto knob_size = 80;


  // Osc pitch controls
  auto osc_pitch_section = bounds.removeFromLeft(knob_size * 3.5);

  juce::FlexBox osc_pitch_section_flx;
  osc_pitch_section_flx.flexDirection = juce::FlexBox::Direction::column;

  juce::FlexBox osc_labels;
  osc_labels.items.add(juce::FlexItem().withWidth(20)); // for alignment
  osc_labels.items.add(juce::FlexItem(lbl_coarse).withFlex(1));
  osc_labels.items.add(juce::FlexItem(lbl_fine).withFlex(1));

  juce::FlexBox osc1_flx;
	osc1_flx.items.add(juce::FlexItem(l_osc1).withWidth(20));
  osc1_flx.items.add(juce::FlexItem(osc1c).withFlex(1));
  osc1_flx.items.add(juce::FlexItem(osc1f).withFlex(1));

  juce::FlexBox osc2_flx;
	osc2_flx.items.add(juce::FlexItem(l_osc2).withWidth(20));
  osc2_flx.items.add(juce::FlexItem(osc2c).withFlex(1));
  osc2_flx.items.add(juce::FlexItem(osc2f).withFlex(1));

  juce::FlexBox osc3_flx;
	osc3_flx.items.add(juce::FlexItem(l_osc3).withWidth(20));
  osc3_flx.items.add(juce::FlexItem(osc3c).withFlex(1));
  osc3_flx.items.add(juce::FlexItem(osc3f).withFlex(1));

  juce::FlexBox osc4_flx;
	osc4_flx.items.add(juce::FlexItem(l_osc4).withWidth(20));
  osc4_flx.items.add(juce::FlexItem(osc4c).withFlex(1));
  osc4_flx.items.add(juce::FlexItem(osc4f).withFlex(1));

	osc_pitch_section_flx.items.add(juce::FlexItem(osc_labels).withHeight(40));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc1_flx).withHeight(knob_size));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc2_flx).withHeight(knob_size));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc3_flx).withHeight(knob_size));
  osc_pitch_section_flx.items.add(juce::FlexItem(osc4_flx).withHeight(knob_size));

  osc_pitch_section_flx.performLayout(osc_pitch_section);

  // Osc FM controls
  auto osc_fm_section = bounds.removeFromLeft(knob_size * 3.0);

  juce::FlexBox osc_fm_section_flx;
  osc_fm_section_flx.flexDirection = juce::FlexBox::Direction::column;

	juce::FlexBox osc_fm_labels;
	osc_fm_labels.items.add(juce::FlexItem(l_oscfm2)
	                        .withHeight(20)
	                        .withWidth(knob_size * 1.0));
	osc_fm_labels.items.add(juce::FlexItem(l_oscfm3)
	                        .withHeight(20)
	                        .withWidth(knob_size * 1.0));
	osc_fm_labels.items.add(juce::FlexItem(l_oscfm4)
	                        .withHeight(20)
	                        .withWidth(knob_size * 1.0));

  juce::FlexBox osc1_fm_flx;
  osc1_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm2)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm3)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));
  osc1_fm_flx.items.add(juce::FlexItem(osc1fm4)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));

  juce::FlexBox osc2_fm_flx;
  osc2_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc2_fm_flx.items.add(juce::FlexItem(osc2fm3)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));
  osc2_fm_flx.items.add(juce::FlexItem(osc2fm4)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));

  juce::FlexBox osc3_fm_flx;
  osc3_fm_flx.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
  osc3_fm_flx.items.add(juce::FlexItem(osc3fm4)
                        .withHeight(knob_size)
                        .withWidth(knob_size * 1.0));

	osc_fm_section_flx.items.add(juce::FlexItem(lbl_fm).withHeight(20));
	osc_fm_section_flx.items.add(juce::FlexItem(osc_fm_labels).withHeight(20));
  osc_fm_section_flx.items.add(juce::FlexItem(osc1_fm_flx).withHeight(knob_size));
  osc_fm_section_flx.items.add(juce::FlexItem(osc2_fm_flx).withHeight(knob_size));
  osc_fm_section_flx.items.add(juce::FlexItem(osc3_fm_flx).withHeight(knob_size));
  osc_fm_section_flx.performLayout(osc_fm_section);

  auto osc_gain_section = bounds.removeFromLeft(knob_size);
  juce::FlexBox osc_gain_section_flx;
  osc_gain_section_flx.flexDirection = juce::FlexBox::Direction::column;
  osc_gain_section_flx.items.add(juce::FlexItem().withHeight(20));
  osc_gain_section_flx.items.add(juce::FlexItem(lbl_gain).withHeight(20));
  osc_gain_section_flx.items.add(juce::FlexItem(osc1g).withHeight(knob_size));
  osc_gain_section_flx.items.add(juce::FlexItem(osc2g).withHeight(knob_size));
  osc_gain_section_flx.items.add(juce::FlexItem(osc3g).withHeight(knob_size));
  osc_gain_section_flx.items.add(juce::FlexItem(osc4g).withHeight(knob_size));
  osc_gain_section_flx.performLayout(osc_gain_section);
}

}
