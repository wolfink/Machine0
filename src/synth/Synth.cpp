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
      _voices[note].Init(event.samplePosition, _sample_rate);
      _voices[note].gain().setTargetValue(0.0);
      _voices[note].gain().reset(_sample_rate, 0.001);
    } else if (message.isNoteOff()) {
      _voices[note].end() = event.samplePosition;
    }
  }

  auto channel0_array = buffer.getWritePointer(0);

  std::vector<int> notes_to_remove;
  notes_to_remove.reserve(MAX_VOICES);
  for (auto& voice : _voices) {
    auto note = voice.first;
    auto& state = voice.second;
    auto delta = TWOPI * juce::MidiMessage::getMidiNoteInHertz(note) / _sample_rate;
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

    state.Set_allpass_freq(0, _sample_rate, MachZParameters::Get_float_value(MachZParameter::ap1));
    state.Set_allpass_freq(1, _sample_rate, MachZParameters::Get_float_value(MachZParameter::ap2));

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
  _last = 0.0;
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

double Synth::VoiceState::Update(double delta)
{
  double curr = sin(_angle += delta);

	// Handle slew distortion
  const double slew = MachZParameters::Get_float_value(MachZParameter::slw1) + 1.0;
  const double slewmod = slew * delta;
  const double slope = curr - _last;
  const int slope_sign = (*(long*) &slope >> 62) + 1;
  curr = (std::abs(slope) > slewmod) ?
    _last + slewmod * slope_sign
    : curr;
  _last = curr;

	// Allpass
  curr = _allpass1.processSingleSampleRaw(curr);
  curr = _allpass2.processSingleSampleRaw(curr);

	// Handle drive distortion
	const double drive = MachZParameters::Get_float_value(MachZParameter::drv1);
	curr *= drive;
	curr = (curr > 1.0) ? 1.0 : (curr < -1.0) ? -1.0 : curr; // clip

  // Update angle
  _angle = ((_angle += delta) > TWOPI)
  	? _angle - TWOPI
  	: _angle;
  return curr * _gain.getNextValue();
}
