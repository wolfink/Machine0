#include "Synth.h"
#include "juce_audio_basics/juce_audio_basics.h"

#define wrap(a, b) ((a) < (b)) ? (a) : (a) - (b)

void Synth::Render(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi_buffer)
{
  for (auto event : midi_buffer)
  {
    auto message = event.getMessage();
    if (message.isNoteOn()) {
      _voices[message.getNoteNumber()] = {
        .env = VoiceState::Ready,
        .angle = 0.0,
        .gain = 0.0,
        .switchpoint = event.samplePosition
      };
    } else if (message.isNoteOff()) {
      _voices[message.getNoteNumber()].switchpoint = event.samplePosition;
    }
  }

  auto channel0_array = buffer.getWritePointer(0);

	std::vector<int> notes_to_remove;
	notes_to_remove.reserve(MAX_VOICES);
  for (auto& voice : _voices) {
    auto note = voice.first;
    auto state = voice.second;
    auto start = (state.env == VoiceState::Ready) ? state.switchpoint : 0;

    // Process active voices
    for (int sample = start; sample < buffer.getNumSamples(); sample++) {
      // Change env on switchpoint
      if (state.switchpoint >= 0 && sample >= state.switchpoint) {
        switch (state.env) {
        case VoiceState::Ready:
          state.env = VoiceState::Attacking;
          state.switchpoint += _attack;
          break;
        case VoiceState::Attacking:
          state.env = VoiceState::Decaying;
          state.switchpoint += _decay;
        case VoiceState::Decaying:
          state.env = VoiceState::Sustaining;
          state.switchpoint = -1;
          break;
        case VoiceState::Sustaining:
          state.env = VoiceState::Releasing;
          state.switchpoint += _release;
          break;
        case VoiceState::Releasing:
          state.env = VoiceState::Finished;
          notes_to_remove.push_back(note);
        default:
          goto voice_end;
        }
      }
      if (state.env != VoiceState::Finished) {
        auto delta = 2*std::numbers::pi*juce::MidiMessage::getMidiNoteInHertz(note) / _sample_rate;

        // Add gain when Active (until max gain), remove when Releasing
        if (state.env == VoiceState::Attacking) {
          state.gain += 1.0 / _attack;
          state.gain = (state.gain > 1.0) ? 1.0 : state.gain;
        } else if (state.env == VoiceState::Releasing) {
          state.gain -= 1.0 / _release;
          state.gain = (state.gain < 0.0) ? 0.0 : state.gain;
        }

        channel0_array[sample] += sin(state.angle += delta) * state.gain;
      }
    }
voice_end:
  	if (state.switchpoint > buffer.getNumSamples()) {
    	state.switchpoint -= buffer.getNumSamples();
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
