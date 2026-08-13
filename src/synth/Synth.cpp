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
      _voices[note] = {
        ._last = 0.0,
        ._angle = 0.0,
        .begin = event.samplePosition,
        .end = -1,
      };
      _voices[note]._gain.setTargetValue(0.0);
      _voices[note]._gain.reset(_sample_rate, 0.001);
    } else if (message.isNoteOff()) {
      _voices[note].end = event.samplePosition;
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
    if (state.begin >= 0) {
      start = state.begin;
      state._gain.setTargetValue(1.0);
      state.begin = -1;
    } else if (state.end >= 0) {
      end = state.end;
      state._gain.setTargetValue(0.0);
      state.end = -1;
    } 

    if (state._gain.getTargetValue() == 0.0
       && state._gain.getCurrentValue() < 0.001) {
      notes_to_remove.push_back(note);
    }

    // Process active voices
    for (int sample = start; sample < buffer.getNumSamples(); sample++) {
      channel0_array[sample] += state.Update(delta) * 0.2;
    }
    _voices[note] = state;
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
