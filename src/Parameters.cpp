#include "Parameters.h"
#include "juce_core/juce_core.h"
#include "juce_events/juce_events.h"

JUCE_IMPLEMENT_SINGLETON(MachZParameters);

MachZParameters::MachZParameters()
{
    auto SlewRange = juce::NormalisableRange<float>(0.0, 1.0);
    SlewParameter = std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("slew"), "Slew", SlewRange, 1.0);
    SlewParameterAttachment = std::make_unique<juce::SliderParameterAttachment>(*SlewParameter, Slew);
    Slew.setNormalisableRange(juce::NormalisableRange<double>(0.0, 1.0));
}
