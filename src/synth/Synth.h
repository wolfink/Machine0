#pragma once

#include <juce_core/juce_core.h>
#include <juce_midi_ci/juce_midi_ci.h>
#include <juce_dsp/juce_dsp.h>
#include "../Parameters.h"
#include "Oscillators.h"

#define Expose(type, name) Expose_##type(name)
#define Expose_r(name) const typeof(_##name)& name() { return _##name; }
#define Expose_rw(name) typeof(_##name)& name() { return _##name; }

class Synth
{

  class VoiceState
  {
  public:
    enum Flags {
      Inactive,
      Active = 1,
      Depressed = 1 << 1,
      Decayed = 1 << 2,
    };
  private:
    int _flags = Inactive;
    int _note = 0;
    double _freq = 0.0;
    Oscillators _oscs;
    double _last1 = 0.0;
    double _last2 = 0.0;
    double _angle1 = 0.0;
    double _angle2 = 0.0;
    double _angle3 = 0.0;
    double _angle4 = 0.0;
    unsigned int _age = 0;
    int _begin = 0;
    int _end = -1;
    int _dist1 = 0;
    int _dist2 = 0;
    double _slw1 = 1.0;
    double _slw2 = 1.0;
    double _drv1 = 1.0;
    double _drv2 = 1.0;
    juce::IIRFilter _allpass1;
    juce::IIRFilter _allpass2;
    juce::SmoothedValue<double> _gain;
 	public:
   	Expose(r, note)
   	Expose(rw, flags)
   	Expose(r, freq)
   	Expose(rw, gain)
   	Expose(rw, begin)
   	Expose(rw, end)
   	Expose(r, age)

   	void Advance_age(unsigned int start) { _age += start; }
   	void Set_note(int note);
   	void Prepare(double sr);
    inline double Update(double sr);
  private:
    inline double Calc_slew(double sample, double& last, double delta, double slew);
    inline double Calc_drive(double sample, double drive);
  };

public:
  constexpr static int MAX_VOICES = 64;
private:
  std::array<VoiceState, MAX_VOICES> _voices;
  bool _sustaining;
  std::set<VoiceState*> _to_end;
  double _sample_rate;
  int _attack=200;
  int _decay=200;
  int _release=200;

public:

  void Set_sample_rate(double sample_rate)
  {
    _sample_rate = sample_rate;
  }

  void Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer);

private:
  void Release_voice(int voice);
};
