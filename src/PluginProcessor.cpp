#include "PluginProcessor.h"
#include "PluginEditor.h"
// #include "dsp/Sound.h"
#include <cmath>
#include "synth/Synth.h"

    // AudioProcessorValueTreeState (AudioProcessor& processorToConnectTo,
    //                               UndoManager* undoManagerToUse,
    //                               const Identifier& valueTreeType,
    //                               ParameterLayout parameterLayout);

namespace mz
{

MachZAudioProcessor::MachZAudioProcessor() :
  juce::AudioProcessor(BusesProperties()
                 .withOutput("Output", juce::AudioChannelSet::stereo(), true))
  //_parameterManager(*this)
{}

MachZAudioProcessor::~MachZAudioProcessor() {}

void MachZAudioProcessor::prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock) 
{
  // dsp::ProcessSpec ps { sampleRate, (uint32) maximumExpectedSamplesPerBlock, 2 };

  // for (int i = 0; i < MAX_VOICES; i++) 
  // {
    // _synth.addVoice(new MachZVoice(_parameterManager, maximumExpectedSamplesPerBlock));
  // }

  // _synth.clearSounds();
  // _synth.addSound(new MachZSound());
  // _synth.setCurrentPlaybackSampleRate(sampleRate);
  // _reverb.setSampleRate(sampleRate);
  // _chorus.prepare(ps);
  // _phaser.prepare(ps);
  // _tremolo.prepare(sampleRate);
  // _delay_l.prepare(ps);
  // _delay_l.setMaximumDelayInSamples(2 * sampleRate);
  // _delay_r.prepare(ps);
  // _delay_r.setMaximumDelayInSamples(2 * sampleRate);
  // _keyboard.reset();
  // _parameterManager.setMaximumBlockSize(maximumExpectedSamplesPerBlock);
  _synth.Set_sample_rate(sampleRate);
}

void MachZAudioProcessor::releaseResources() 
{

}

void MachZAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer) 
{
  auto num_samples = buffer.getNumSamples();
  // auto out          = *_parameterManager.getParameterValueTable(Parameters::Out, 0);
  // int  reverb_on    = *_parameterManager.getParameterValueTable(Parameters::ReverbOn, 0);
  // int  delay_on     = *_parameterManager.getParameterValueTable(Parameters::DelayOn, 0);
  // int  chorus_on    = *_parameterManager.getParameterValueTable(Parameters::ChorusOn, 0);
  // int  tremolo_on   = *_parameterManager.getParameterValueTable(Parameters::TremoloOn, 0);
  // int  phaser_on    = *_parameterManager.getParameterValueTable(Parameters::PhaserOn, 0);

  juce::dsp::AudioBlock<float> in_block(buffer);
  juce::dsp::ProcessContextReplacing<float> mod_context(in_block);

  buffer.clear();
  _keyboard.processNextMidiBuffer(midi_buffer, 0, num_samples, true);
  _synth.Render(buffer, midi_buffer);

  // buffer.applyGain((_notes_down) ? 1 : 0);
  // _synth.renderNextBlock(buffer, midi_buffer, 0, num_samples);

  // Handle effects

  // if (chorus_on) {
    // auto chorus_mix   = *_parameterManager.getParameterValueTable(Parameters::ChorusMix, 0);
    // auto chorus_rate  = *_parameterManager.getParameterValueTable(Parameters::ChorusRate, 0);
    // auto chorus_depth = *_parameterManager.getParameterValueTable(Parameters::ChorusDepth, 0);

    // _chorus.setRate(chorus_rate);
    // _chorus.setDepth(chorus_depth / 100.0);
    // _chorus.setFeedback(0.2);
    // _chorus.setMix(0.5);

    // _chorus.process(mod_context);
  // }

  // if (phaser_on) {
  //   auto phaser_rate  = *_parameterManager.getParameterValueTable(Parameters::PhaserRate, 0);
  //   auto phaser_depth = *_parameterManager.getParameterValueTable(Parameters::PhaserDepth, 0);

  //   _phaser.setRate(phaser_rate);
  //   _phaser.setDepth(phaser_depth / 100.0);
  //   _phaser.setMix(0.5);

  //   _phaser.process(mod_context);
  // }

  // if (tremolo_on) {
  //   auto trem_rate    = *_parameterManager.getParameterValueTable(Parameters::TremoloRate, 0);
  //   auto trem_depth   = *_parameterManager.getParameterValueTable(Parameters::TremoloDepth, 0);
  //   _tremolo.setFrequency(trem_rate);

  //   for (int channel = 0; channel < 2; channel++) {
  //     auto writep = buffer.getWritePointer(channel);
  //     for (int sample = 0; sample < num_samples; sample++) {
  //       writep[sample] *= 1 - trem_depth * 0.005 * (_tremolo.get(sample) + 1);
  //     }
  //   }
  // }

  // if (delay_on) {
  //   auto delay_type   = *_parameterManager.getParameterValueTable(Parameters::DelayType, 0);
  //   auto delay_time   = *_parameterManager.getParameterValueTable(Parameters::DelayTime, 0);
  //   auto delay_level  = *_parameterManager.getParameterValueTable(Parameters::DelayLevel, 0);
  //   auto delay_fb     = *_parameterManager.getParameterValueTable(Parameters::DelayFeedback, 0);
  //   AudioBuffer<float> buffer_copy(buffer.getNumChannels(), buffer.getNumSamples());

  //   auto delay_time_samp = delay_time * 0.001 * getSampleRate();
  //   for (int channel = 0; channel < 2; channel++)
  //   {
  //     buffer_copy.copyFrom(channel, 0, buffer, channel, 0, buffer.getNumSamples());
  //     auto writep = buffer.getWritePointer(channel);
  //     auto play_ch = 0;
  //     for (int sample = 0; sample < num_samples; sample++) {
  //       const auto f = delay_fb * 0.01;
  //       const auto g = Decibels::decibelsToGain(delay_level);

  //       const auto x = writep[sample];
  //       const auto x_del = _delay_r.popSample(channel, delay_time_samp);
  //       if (channel == 1) _delay_r.pushSample(channel, x);
  //       float y;
  //       // Ping-pong vs single delay
  //       if (delay_type == 1) {
  //         y = _delay_l.popSample(channel, 2 * delay_time_samp) + x_del;
  //         if (channel == 1) _delay_l.pushSample(channel, x_del + f * y);
  //         else _delay_l.pushSample(channel, x + f * y);
  //       }
  //       else {
  //         y = _delay_l.popSample(channel, delay_time_samp);
  //         _delay_l.pushSample(channel, x + f * y);
  //       }

  //       writep[sample] += g * y;
  //     }
  //   }
  // }

  // if (reverb_on) {
  //   auto reverb_time  = *_parameterManager.getParameterValueTable(Parameters::ReverbTime, 0);
  //   auto reverb_level = *_parameterManager.getParameterValueTable(Parameters::ReverbLevel, 0);

  //   _reverb.setParameters(Reverb::Parameters { reverb_time * 0.1f, 0.25f, Decibels::decibelsToGain(reverb_level), 0.5f, 1.0, 0.0 });

  //   _reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), num_samples);
  // }

  // _parameterManager.forwardLFOS(num_samples);
  // _tremolo.forward(num_samples);

  // buffer.applyGain(Decibels::decibelsToGain(out));
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

