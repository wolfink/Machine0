#include "PluginProcessor.h"
#include "PluginEditor.h"
// #include "dsp/Sound.h"
#include <cmath>
#include "synth/Synth.h"

namespace mz
{

MachZAudioProcessor::MachZAudioProcessor() :
  juce::AudioProcessor(BusesProperties()
                 .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{}

MachZAudioProcessor::~MachZAudioProcessor() {}

void MachZAudioProcessor::prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock) 
{
  _synth.Set_sample_rate(sampleRate);
}

void MachZAudioProcessor::releaseResources() 
{

}

void MachZAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer) 
{
  auto num_samples = buffer.getNumSamples();

  juce::dsp::AudioBlock<float> in_block(buffer);
  juce::dsp::ProcessContextReplacing<float> mod_context(in_block);

  buffer.clear();
  _keyboard.processNextMidiBuffer(midi_buffer, 0, num_samples, true);
  _synth.Render(buffer, midi_buffer);

  buffer.applyGain(0.125);
}

void MachZAudioProcessor::reset() 
{

}

juce::AudioProcessorEditor* MachZAudioProcessor::createEditor() 
{
  return new MachZProcessorEditor(*this);
}

int MachZAudioProcessor::getNumPrograms() 
{
  return 1;
}

int MachZAudioProcessor::getCurrentProgram() 
{
  return 0;
}

void MachZAudioProcessor::setCurrentProgram (int index) 
{

}

const juce::String MachZAudioProcessor::getProgramName (int index) 
{
  return "init";
}

void MachZAudioProcessor::changeProgramName (int index, const juce::String& newName) 
{

}

void MachZAudioProcessor::getStateInformation (juce::MemoryBlock& destData) 
{

}

void MachZAudioProcessor::setStateInformation (const void* data, int sizeInBytes) 
{

}

}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new mz::MachZAudioProcessor();
}

