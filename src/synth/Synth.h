#pragma once

#include <juce_core/juce_core.h>
#include <juce_midi_ci/juce_midi_ci.h>
#include "../Parameters.h"

class Synth
{
  struct VoiceState
  {
    enum Envelope {
      Ready,
      Attacking,
      Decaying,
      Sustaining,
      Releasing,
      Finished
    } env;
    float angle;
    float gain;
    int switchpoint;
  };

public:
  constexpr static int MAX_VOICES = 64;
private:
  std::unordered_map<int, VoiceState> _voices;
  float _sample_rate;
  int _attack=200;
  int _decay=200;
  int _release=200;

public:
  Synth()
  {
    _voices.reserve(MAX_VOICES);
  }

  void Set_sample_rate(float sample_rate)
  {
    _sample_rate = sample_rate;
  }

  void Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer);

private:
  void Release_voice(int voice);
};
