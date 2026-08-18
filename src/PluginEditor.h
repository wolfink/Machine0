#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
// #include <gui.h>
#include "PluginProcessor.h"
#include "gui/GeneratorPanel.h"
#include "gui/OscPanel.h"
#include "gui/LookAndFeel.h"

namespace mz
{

class MachZProcessorEditor : public juce::AudioProcessorEditor
{
  LookAndFeel _lookAndFeel;

  // MixerPanel _mixPanel;
  GeneratorPanel _genPanel;
  OscPanel _oscPanel;
  // ModPanel   _modPanel;
  // FXPanel    _fxPanel;

public:
  MachZProcessorEditor(MachZAudioProcessor& a);
  void paint(juce::Graphics& g) override;
  void resized() override;
private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MachZProcessorEditor)
};

}
