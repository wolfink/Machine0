#pragma once

#include <juce_core/juce_core.h>
#include <juce_midi_ci/juce_midi_ci.h>
#include <juce_dsp/juce_dsp.h>
#include "../Parameters.h"

#define Expose(type,...) Expose##type(__VA_ARGS__)
#define ExposeRO(type, name) const type& name() { return _##name; }
#define ExposeRW(type, name) type& name() { return _##name; }

class Synth
{
  class VoiceState
  {
    double _last;
    double _angle;
    int _begin;
    int _end;
    juce::IIRFilter _allpass1;
    juce::IIRFilter _allpass2;
    juce::SmoothedValue<double> _gain;
 	public:
   	Expose(RW, juce::SmoothedValue<double>, gain)
   	Expose(RW, int, begin)
   	Expose(RW, int, end)

   	VoiceState() : _last(0.0), _angle(0.0), _begin(0), _end(0) {};
   	void Init(int begin, double sr);
   	void Set_allpass_freq(int index, double sr, double freq);
    double Update(double delta);
  };

public:
  constexpr static int MAX_VOICES = 64;
private:
  std::unordered_map<int, VoiceState> _voices;
  double _sample_rate;
  int _attack=200;
  int _decay=200;
  int _release=200;

public:
  Synth()
  {
    _voices.reserve(MAX_VOICES);
  }

  void Set_sample_rate(double sample_rate)
  {
    _sample_rate = sample_rate;
  }

  void Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer);

private:
  void Release_voice(int voice);
};
