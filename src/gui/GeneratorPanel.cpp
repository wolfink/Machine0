#include "../Parameters.h"
#include "GeneratorPanel.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace mz
{

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
  _l_dist.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_dist.setText("Distortion", juce::NotificationType::dontSendNotification);
  _l_dist.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_dist.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_dist);


  _l_pass1.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_pass1.setText("1st Pass", juce::NotificationType::dontSendNotification);
  _l_pass1.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_pass1.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_pass1);

  _slw1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _slw1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_slw1);

  _drv1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _drv1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_drv1);

  _dist1type.onChange = [this]() {
    resized();
  };
  addAndMakeVisible(_dist1type);


  _l_ap.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_ap.setText("Allpass", juce::NotificationType::dontSendNotification);
  _l_ap.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_ap.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_ap);

  _l_apkt.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_apkt.setText("Keytracking", juce::NotificationType::dontSendNotification);
  _l_apkt.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_apkt.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_apkt);

  _apkt.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _apkt.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_apkt);

  _l_ap1.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_ap1.setText("1", juce::NotificationType::dontSendNotification);
  _l_ap1.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_ap1.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_ap1);

  _ap1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _ap1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
  addAndMakeVisible(_ap1);

  _l_ap2.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_ap2.setText("2", juce::NotificationType::dontSendNotification);
  _l_ap2.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_ap2.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_ap2);

  _ap2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _ap2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
  addAndMakeVisible(_ap2);


  _l_pass2.setFont(juce::Font(16.0f, juce::Font::bold));
  _l_pass2.setText("2nd Pass", juce::NotificationType::dontSendNotification);
  _l_pass2.setColour(juce::Label::textColourId, juce::Colours::linen);
  _l_pass2.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(_l_pass2);

  _slw2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _slw2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_slw2);

  _drv2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  _drv2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0, 0.0);
  addAndMakeVisible(_drv2);

  _dist2type.onChange = [this]() {
    resized();
  };
  addAndMakeVisible(_dist2type);

}

void GeneratorPanel::resized()
{
  auto bounds = getLocalBounds();
  auto knob_size = 80;
  auto combo_size = 20;
  auto text_height = combo_size;
  auto text_width = 100;
  auto col_width = 150;


	auto header = bounds.removeFromTop(40);
	_l_dist.setBounds(header);


	auto label_section = bounds.removeFromLeft(text_width + 20);
	juce::FlexBox label_flx;
	label_flx.flexDirection = juce::FlexBox::Direction::column;

  label_flx.items.add(juce::FlexItem(_l_pass1)
                      .withHeight(knob_size));
	label_flx.items.add(juce::FlexItem(_l_ap)
	                    .withHeight(knob_size + 40));
  label_flx.items.add(juce::FlexItem(_l_pass2)
                      .withHeight(knob_size));
  label_flx.performLayout(label_section);


  auto dist1_section = bounds.removeFromTop(knob_size);
  juce::FlexBox dist1_flex;
  dist1_flex.alignItems = juce::FlexBox::AlignItems::center;
  dist1_flex.items.add(juce::FlexItem(_dist1type)
                       .withHeight(combo_size)
                       .withWidth(col_width));

  _slw1.setVisible(false);
  _drv1.setVisible(false);
  if (_dist1type.getSelectedItemIndex() == 0) {
    _slw1.setVisible(true);
    dist1_flex.items.add(juce::FlexItem(_slw1)
                         .withHeight(knob_size)
                         .withWidth(col_width));
  } else {
    _drv1.setVisible(true);
    dist1_flex.items.add(juce::FlexItem(_drv1)
                         .withHeight(knob_size)
                         .withWidth(col_width));
  }

  dist1_flex.performLayout(dist1_section);


	auto allpass_headers = bounds.removeFromTop(20);
	juce::FlexBox aph_flx;
	aph_flx.items.add(juce::FlexItem(_l_apkt).withWidth(col_width));
	aph_flx.items.add(juce::FlexItem(_l_ap1).withWidth(col_width));
	aph_flx.items.add(juce::FlexItem(_l_ap2).withWidth(col_width));
	aph_flx.performLayout(allpass_headers);

  auto allpass_section = bounds.removeFromTop(knob_size + 20);
  juce::FlexBox allpass;
  //allpass.alignItems = juce::FlexBox::AlignItems::center;
  allpass.items.add(juce::FlexItem(_apkt)
                    .withHeight(knob_size)
                    .withWidth(col_width));
  allpass.items.add(juce::FlexItem(_ap1)
                    .withWidth(col_width));
  allpass.items.add(juce::FlexItem(_ap2)
                    .withWidth(col_width));
  allpass.performLayout(allpass_section);


  auto dist2_section = bounds.removeFromTop(knob_size);
  juce::FlexBox dist2_flex;
  dist2_flex.alignItems = juce::FlexBox::AlignItems::center;
  dist2_flex.items.add(juce::FlexItem(_dist2type)
                       .withHeight(combo_size)
                       .withWidth(col_width));

  _slw2.setVisible(false);
  _drv2.setVisible(false);
  if (_dist2type.getSelectedItemIndex() == 0) {
    _slw2.setVisible(true);
    dist2_flex.items.add(juce::FlexItem(_slw2)
                         .withHeight(knob_size)
                         .withWidth(col_width));
  } else {
    _drv2.setVisible(true);
    dist2_flex.items.add(juce::FlexItem(_drv2)
                         .withHeight(knob_size)
                         .withWidth(col_width));
  }

  dist2_flex.performLayout(dist2_section);
}

}
