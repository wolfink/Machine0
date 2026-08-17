#include "Oscillators.h"
#include "../Parameters.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_core/juce_core.h"

void Oscillators::Prepare(int note)
{
  _osc1_freq = Get_osc_to_freq(note, 0);
  _osc2_freq = Get_osc_to_freq(note, 1);
  _osc3_freq = Get_osc_to_freq(note, 2);
  _osc4_freq = Get_osc_to_freq(note, 3);
  _osc1_fm2 = MachZParameters::Get_float_value(MachZParameter::osc1fm2);
  _osc1_fm3 = MachZParameters::Get_float_value(MachZParameter::osc1fm3);
  _osc1_fm4 = MachZParameters::Get_float_value(MachZParameter::osc1fm4);
  _osc2_fm3 = MachZParameters::Get_float_value(MachZParameter::osc2fm3);
  _osc2_fm4 = MachZParameters::Get_float_value(MachZParameter::osc2fm4);
  _osc3_fm4 = MachZParameters::Get_float_value(MachZParameter::osc3fm4);
  _osc1_gain = MachZParameters::Get_float_value(MachZParameter::osc1g);
  _osc2_gain = MachZParameters::Get_float_value(MachZParameter::osc2g);
  _osc3_gain = MachZParameters::Get_float_value(MachZParameter::osc3g);
  _osc4_gain = MachZParameters::Get_float_value(MachZParameter::osc4g);
}

double Oscillators::OutputNext(double sr, double& a1, double& a2, double& a3, double& a4)
{
  auto TWOPI = juce::MathConstants<double>::twoPi;
  auto o1_delta = TWOPI * _osc1_freq / sr;
  auto o2_delta = TWOPI * _osc2_freq / sr;
  auto o3_delta = TWOPI * _osc3_freq / sr;
  auto o4_delta = TWOPI * _osc4_freq / sr;
  auto o1_out = sin(a1 += o1_delta);
  auto o2_out = sin(a2 += o2_delta);
  auto o3_out = sin(a3 += o3_delta);
  auto o4_out = sin(a4 += o4_delta);
  a1 = (a1 > TWOPI) ? a1 - TWOPI : a1;
  a2 = (a2 > TWOPI) ? a2 - TWOPI : a2;
  a3 = (a3 > TWOPI) ? a3 - TWOPI : a3;
  a4 = (a4 > TWOPI) ? a4 - TWOPI : a4;
  return 
  	  o1_out * _osc1_gain
  	+ o2_out * _osc2_gain
  	+ o3_out * _osc3_gain
  	+ o4_out * _osc4_gain;
}

double Oscillators::Get_osc_to_freq(int note, int index)
{
  double base_freq = juce::MidiMessage::getMidiNoteInHertz(note);
  double mult = 1.0;
  switch(index) {
  case 0:
    mult = MachZParameters::Get_int_value(MachZParameter::osc1c);
    mult += MachZParameters::Get_float_value(MachZParameter::osc1f);
    break;
  case 1:
    mult = MachZParameters::Get_int_value(MachZParameter::osc2c);
    mult += MachZParameters::Get_float_value(MachZParameter::osc2f);
    break;
  case 2:
    mult = MachZParameters::Get_int_value(MachZParameter::osc3c);
    mult += MachZParameters::Get_float_value(MachZParameter::osc3f);
    break;
  case 3:
    mult = MachZParameters::Get_int_value(MachZParameter::osc4c);
    mult += MachZParameters::Get_float_value(MachZParameter::osc4f);
    break;
  }
  return mult * base_freq;
}
