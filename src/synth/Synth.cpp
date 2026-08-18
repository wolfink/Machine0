#include "Synth.h"
#include "juce_core/juce_core.h"
#include <juce_audio_basics/juce_audio_basics.h>

namespace mz
{

const auto TWOPI = juce::MathConstants<double>::twoPi;

void Synth::Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer)
{
  for (auto event : midi_buffer)
  {
    auto message = event.getMessage();
    auto note = message.getNoteNumber();
    if (message.isNoteOn()) {
      int voice_idx = -1;
      unsigned int max_age = 0;
      unsigned int max_age_idx = 0;
      // try to find inactive voices, keep track of oldest voices
      for (int i = 0; i < MAX_VOICES; i++) {
        auto& v = _voices[i];
        // use first inactive voice if available
        if (~v.flags() & VoiceState::Active) {
          voice_idx = i;
          break;
        }
        if (v.age() > max_age) {
          max_age = v.age();
          max_age_idx = i;
        }
      }
      // use oldest voice if all voices active
      if (voice_idx < 0) {
        voice_idx = max_age_idx;
      }
      auto& v = _voices[voice_idx];
      v.Set_note(note);
      v.gain().setTargetValue(0.0);
      v.gain().reset(_sample_rate, 0.001);
      v.begin() = event.samplePosition;
      v.end() = -1;
      v.flags() |= VoiceState::Depressed | VoiceState::Active;
    } else if (message.isNoteOff()) {
      for (int i = 0; i < MAX_VOICES; i++) {
        auto& v = _voices[i];
        if (v.note() == note) {
          v.end() = event.samplePosition;
        }
      }
    } else if (message.isSustainPedalOn()) {
      _sustaining = true;
    } else if (message.isSustainPedalOff()) {
      _sustaining = false;
      for (int i = 0; i < MAX_VOICES; i++) {
        auto &v = _voices[i];
        // end notes that are not currently depressed
        if (~v.flags() & VoiceState::Depressed) {
          v.end() = event.samplePosition;
        }
      }
    }
  }

  auto channel0_array = buffer.getWritePointer(0);

  for (auto& voice : _voices)
  if (voice.flags() & VoiceState::Active) {
    int start = 0;

    // if note is beginning, set start to beginning sample
    if (voice.begin() >= 0) {
      start = voice.begin();
      voice.gain().setTargetValue(1.0);
      voice.begin() = -1;
    } else if (voice.end() >= 0) { // if note is ending, unset depressed flag
      voice.end() = -1;
      voice.flags() &= ~VoiceState::Depressed;
      if (!_sustaining) {
        voice.gain().setTargetValue(0.0);
      }
    } 

    if (~voice.flags() & VoiceState::Depressed
        && voice.gain().getCurrentValue() < 0.001) {
      voice.flags() = VoiceState::Inactive;
    }


		voice.Prepare(_sample_rate);
    // Process active voices
    for (int sample = start; sample < buffer.getNumSamples(); sample++) {
      channel0_array[sample] += voice.Update(_sample_rate) * 0.2;
    }
    voice.Advance_age(start);
  }

  // Copy channel 0 to all channels
  for (int channel = 1; channel < buffer.getNumChannels(); channel++)
  {
    auto channel_array = buffer.getWritePointer(channel);
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
      channel_array[sample] = channel0_array[sample];
    }
  }
}

void Synth::VoiceState::Set_note(int note)
{ 
 	_note = note;
 	_age = 0;
}

void Synth::VoiceState::Prepare(double sr)
{
   	_freq = juce::MidiMessage::getMidiNoteInHertz(_note);

    auto apkt = MachZParameters::Get_float_value(MachZParameter::apkt);
    auto ap_frac = apkt * (_freq / 440.0 - 1) + 1;

    auto ap1_freq = ap_frac * MachZParameters::Get_float_value(MachZParameter::ap1);
    auto ap1_coeff = juce::IIRCoefficients::makeAllPass(sr, ap1_freq);
    _allpass1.setCoefficients(ap1_coeff);

    auto ap2_freq = ap_frac * MachZParameters::Get_float_value(MachZParameter::ap2);
    auto ap2_coeff = juce::IIRCoefficients::makeAllPass(sr, ap2_freq);
    _allpass2.setCoefficients(ap2_coeff);
  
    _dist1 = MachZParameters::Get_choice(MachZParameter::dist1type);
    _dist2 = MachZParameters::Get_choice(MachZParameter::dist2type);

    _slw1 =  MachZParameters::Get_float_value(MachZParameter::slw1) + 1.0;
    _slw2 =  MachZParameters::Get_float_value(MachZParameter::slw2) + 1.0;
    _drv1 =  MachZParameters::Get_float_value(MachZParameter::drv1);
    _drv2 =  MachZParameters::Get_float_value(MachZParameter::drv2);

    _oscs.Prepare(_note);
}

double Synth::VoiceState::Update(double sr)
{
  double delta = TWOPI * _freq / sr;
  double sample = _oscs.OutputNext(sr, _angle1, _angle2, _angle3, _angle4);

  // Distortion pass 1
	sample = (_dist1)
		? Calc_drive(sample, _drv1)
		: Calc_slew(sample, _last1, delta, _slw1);

  // Allpass (in parallel)
  auto temp = sample;
  sample = _allpass1.processSingleSampleRaw(temp) * 0.5;
  sample += _allpass2.processSingleSampleRaw(temp) * 0.5;

	// Distortion pass 2
	sample = (_dist2)
		? Calc_drive(sample, _drv2)
		: Calc_slew(sample, _last2, delta, _slw2);

  // Update angle
  // _angle1 = ((_angle1 += delta) > TWOPI)
  //   ? _angle1 - TWOPI
  //   : _angle1;
  return sample * _gain.getNextValue();
}

double Synth::VoiceState::Calc_slew(double sample, double& last, double delta, double slew)
{
  const double slope = sample - last;
  const int slope_sign = (*(long*) &slope >> 62) + 1;
  const double slewmod = slew * delta;
  last = (std::abs(slope) > slewmod) ?
    last + slewmod * slope_sign
    : sample;
  return last;
}

double Synth::VoiceState::Calc_drive(double sample, double drive)
{
  sample *= drive;
  sample = (sample > 1.0) ? 1.0 : (sample < -1.0) ? -1.0 : sample; // clip
  return sample;
}

}
