#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mz
{

class OscPanel : public juce::Component
{
  juce::Label lbl_coarse;
  juce::Label lbl_fine;

  juce::Slider& osc1c;
  juce::Slider& osc1f;
  juce::Label l_osc1;

  juce::Slider& osc2c;
  juce::Slider& osc2f;
  juce::Label l_osc2;

  juce::Slider& osc3c;
  juce::Slider& osc3f;
  juce::Label l_osc3;

  juce::Slider& osc4c;
  juce::Slider& osc4f;
  juce::Label l_osc4;


  juce::Label lbl_fm;
  juce::Label l_oscfm2;
  juce::Label l_oscfm3;
  juce::Label l_oscfm4;

  juce::Slider& osc1fm2;
  juce::Slider& osc1fm3;
  juce::Slider& osc1fm4;
  juce::Slider& osc2fm3;
  juce::Slider& osc2fm4;
  juce::Slider& osc3fm4;


  juce::Label lbl_gain;
  juce::Slider& osc1g;
  juce::Slider& osc2g;
  juce::Slider& osc3g;
  juce::Slider& osc4g;

public:
  OscPanel();
  virtual void resized() override;
};

}
