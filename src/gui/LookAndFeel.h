#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace mz {
  class LookAndFeel : public juce::LookAndFeel_V4
  {
  public:
    LookAndFeel()
    {
      setColourScheme(
        ColourScheme(
            juce::Colour(0x6F6F9FFF), // windowBackground
            juce::Colour(0x6F6F9FFF), // widgetBackground
            juce::Colour(0x6F6F9FFF), // menuBackground
            juce::Colours::linen,     // outline
            juce::Colours::linen,     // defaultText
            juce::Colour(0x6F6F9FFF), // defaultFill
            juce::Colours::linen,     // highlightedText
            juce::Colours::peru,      // highlightedFill
            juce::Colour(0x6F6F9FFF)  // menuText
        )
      );
    }
  };
}
