#include "Parameters.h"
#include "juce_core/juce_core.h"
#include "juce_events/juce_events.h"
#include <cmath>

JUCE_IMPLEMENT_SINGLETON(MachZParameters);

MachZParameters::MachZParameters()
{
  ParameterList(Attach)
}

double MachZParameters::Get_float_value(const MachZParameter& parameter)
{
  switch (parameter)
  {
  ParameterList(GetFloatValue)
  default:
    return NAN;
  }
}

juce::Slider& MachZParameters::Get_slider(const MachZParameter& parameter)
{
  switch (parameter)
  {
  ParameterList(GetSlider)
 	default:
    return getInstance()->_slw1;
  }
}
