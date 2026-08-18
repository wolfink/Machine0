#pragma once

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace mz
{

class GeneratorPanel : public juce::Component
{
  juce::Label _l_dist;


  juce::Label _l_pass1;
  juce::Slider& _slw1;
  juce::Slider& _drv1;
  juce::ComboBox& _dist1type;


  juce::Label _l_ap;

  juce::Label _l_apkt;
  juce::Slider& _apkt;

  juce::Label _l_ap1;
  juce::Slider& _ap1;

  juce::Label _l_ap2;
  juce::Slider& _ap2;


  juce::Label _l_pass2;
  juce::Slider& _slw2;
  juce::Slider& _drv2;
  juce::ComboBox& _dist2type;

public:
    GeneratorPanel();
    virtual void resized() override;
};

}
