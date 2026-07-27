#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
#include "synth/Synth.h"
//#include <defs.h>
//#include "ParameterManager.h"

using namespace juce;

class MachZAudioProcessor : public AudioProcessor
{
  #if !NDEBUG
  static constexpr int MAX_VOICES = 1;
  #else
  static constexpr int MAX_VOICES = 8;
  #endif

  ////////////////////
  // Data           //
  ////////////////////

  // ParameterManager _parameterManager;
  // Synthesiser _synth;
  // Reverb _reverb;
  // dsp::Chorus<float> _chorus;
  // Oscillator _tremolo;
  // dsp::Phaser<float> _phaser;
  // dsp::DelayLine<float> _delay_l;
  // dsp::DelayLine<float> _delay_r;
  // int _ping_pong_channel = 0;
  // float _delay_index = 0.0;
  MidiKeyboardState _keyboard;
  Synth _synth;
  float _x = 0.0;
  int _notes_down = 0;
public:

  MachZAudioProcessor();
  ~MachZAudioProcessor();

  // AudioProcessorValueTreeState& getState() { return _state; }
  const String getName() const override { return "Machine0 Synth"; }

  //ParameterManager& getParameterManager() { return _parameterManager; }

  void prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock) override;
  void releaseResources() override;
  void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

  double getTailLengthSeconds() const override { return 0.0; }
  bool acceptsMidi() const override { return true; };
  bool producesMidi() const override { return false; };

  void reset() override;
  AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override { return true; };

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const String getProgramName (int index) override;
  void changeProgramName (int index, const String& newName) override;

  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MachZAudioProcessor)
};
