#include "Synth.h"
#include <juce_audio_basics/juce_audio_basics.h>

const auto TWOPI = 2 * std::numbers::pi;

void Synth::Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer)
{
  for (auto event : midi_buffer)
  {
    auto message = event.getMessage();
    auto note = message.getNoteNumber();
    if (message.isNoteOn()) {
      if (_sustaining && _to_end.contains(note)) { // don't re-init note
        _to_end.erase(note); // note is no longer ending
      } else {
        _voices[note].Init(event.samplePosition, _sample_rate);
        _voices[note].gain().setTargetValue(0.0);
        _voices[note].gain().reset(_sample_rate, 0.001);
      }
    } else if (message.isNoteOff()) {
      if (_sustaining) {
        _to_end.insert(note);
      } else { // if not sustaining, end the note
        _voices[note].end() = event.samplePosition;
      }
    } else if (message.isSustainPedalOn()) {
      _sustaining = true;
    } else if (message.isSustainPedalOff()) {
      // end all voices that are no longer being depressed
      for (auto note : _to_end) {
        _voices[note].end() = event.samplePosition;
      }
      _to_end.clear();
      _sustaining = false;
    }
  }

  auto channel0_array = buffer.getWritePointer(0);

  std::vector<int> notes_to_remove;
  notes_to_remove.reserve(MAX_VOICES);
  for (auto& voice : _voices) {
    auto note = voice.first;
    auto& state = voice.second;
    auto freq = juce::MidiMessage::getMidiNoteInHertz(note);
    auto delta = TWOPI * freq / _sample_rate;
    int start = 0;
    int end = buffer.getNumSamples();
    if (state.begin() >= 0) {
      start = state.begin();
      state.gain().setTargetValue(1.0);
      state.begin() = -1;
    } else if (state.end() >= 0) {
      end = state.end();
      state.gain().setTargetValue(0.0);
      state.end() = -1;
    } 

    if (state.gain().getTargetValue() == 0.0
       && state.gain().getCurrentValue() < 0.001) {
      notes_to_remove.push_back(note);
    }

		auto apkt = MachZParameters::Get_float_value(MachZParameter::apkt);
    auto ap_frac = apkt * (freq / 440.0 - 1) + 1;
    auto ap1_freq = ap_frac * MachZParameters::Get_float_value(MachZParameter::ap1);
    auto ap2_freq = ap_frac * MachZParameters::Get_float_value(MachZParameter::ap2);
    state.Set_allpass_freq(0, _sample_rate, ap1_freq);
    state.Set_allpass_freq(1, _sample_rate, ap2_freq);

    // Process active voices
    for (int sample = start; sample < buffer.getNumSamples(); sample++) {
      channel0_array[sample] += state.Update(delta) * 0.2;
    }
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

  // Remove notes that have ended
  for (auto note : notes_to_remove)
  {
    _voices.erase(note);
  }
}

void Synth::VoiceState::Init(int begin, double sr)
{
  _last1 = 0.0;
  _last2 = 0.0;
  _angle = 0.0;
  _begin = begin;
  _end = -1;
  _allpass1.reset();
  _allpass2.reset();
  Set_allpass_freq(0, sr, MachZParameters::Get_float_value(MachZParameter::ap1));
  Set_allpass_freq(1, sr, MachZParameters::Get_float_value(MachZParameter::ap2));
}

void Synth::VoiceState::Set_allpass_freq(int index, double sr, double freq)
{
  auto ap_coeff = juce::IIRCoefficients::makeAllPass(sr, freq);
  if (index == 0) {
    _allpass1.setCoefficients(ap_coeff);
  } else {
    _allpass2.setCoefficients(ap_coeff);
  }
}

inline double calc_slew(double sample, double& last, double delta, double slew)
{
  const double slope = sample - last;
  const int slope_sign = (*(long*) &slope >> 62) + 1;
  const double slewmod = slew * delta;
  last = (std::abs(slope) > slewmod) ?
    last + slewmod * slope_sign
    : sample;
  return last;
}

inline double calc_drive(double sample, double drive)
{
  sample *= drive;
  sample = (sample > 1.0) ? 1.0 : (sample < -1.0) ? -1.0 : sample; // clip
  return sample;
}

double Synth::VoiceState::Update(double delta)
{
  double sample = sin(_angle += delta);

  // Handle distortion pass 1
  if (MachZParameters::Get_choice(MachZParameter::dist1type) == 0) {
    sample = calc_slew(sample, _last1, delta, MachZParameters::Get_float_value(MachZParameter::slw1) + 1.0);
  } else {
    sample = calc_drive(sample, MachZParameters::Get_float_value(MachZParameter::drv1));
  }

  // Allpass (in parallel)
  auto sap1 = sample;
  auto sap2 = sample;
  sample = _allpass1.processSingleSampleRaw(sap1) * 0.5;
  sample += _allpass2.processSingleSampleRaw(sap2) * 0.5;

  if (MachZParameters::Get_choice(MachZParameter::dist2type) == 0) {
    sample = calc_slew(sample, _last2, delta, MachZParameters::Get_float_value(MachZParameter::slw2) + 1.0);
  } else {
    sample = calc_drive(sample, MachZParameters::Get_float_value(MachZParameter::drv2));
  }

  // Update angle
  _angle = ((_angle += delta) > TWOPI)
    ? _angle - TWOPI
    : _angle;
  return sample * _gain.getNextValue();
}
