#include "PluginEditor.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace mz
{

typedef juce::LookAndFeel_V4::ColourScheme::UIColour UIColour;

MachZProcessorEditor::MachZProcessorEditor(MachZAudioProcessor& a) :
  AudioProcessorEditor(a)
  // _mixPanel(a),
  // _genPanel(a),
  // _modPanel(a),
  // _fxPanel(a)
{
  setLookAndFeel(&_lookAndFeel);
  // addAndMakeVisible(_mixPanel);
  addAndMakeVisible(_genPanel);
  addAndMakeVisible(_oscPanel);
  // addAndMakeVisible(_modPanel);
  // addAndMakeVisible(_fxPanel);
  setSize(900, 800);
  //  Colour::fromRGB(30, 30, 128)
}

void MachZProcessorEditor::paint(juce::Graphics& g)
{
  auto bg_color = _lookAndFeel
    .getCurrentColourScheme()
    .getUIColour(UIColour::windowBackground);
  const auto default_text = _lookAndFeel
    .getCurrentColourScheme()
    .getUIColour(UIColour::defaultText);
  const auto default_fill = _lookAndFeel
    .getCurrentColourScheme()
    .getUIColour(UIColour::defaultFill);
  const auto title_color = default_text;
  const auto hl_text = _lookAndFeel
    .getCurrentColourScheme()
    .getUIColour(UIColour::highlightedText);

  const auto center_x = getWidth() * 0.5;
  const auto text_width = 150.0;
  const auto title_size = 25.0;
  const auto info_size  = 18.0;
  const auto text_x   = 20.0;
  const auto text_y   = 10.0;
  const juce::Font title_font(title_size, juce::Font::FontStyleFlags::bold);
  const juce::Font info_font(info_size, juce::Font::FontStyleFlags::bold);

  g.fillAll(bg_color);

  g.setColour(default_fill);
  g.fillRoundedRectangle(text_x, text_y, text_width, title_size + text_y, 15.0);

  g.setColour(title_color);
  g.setFont (title_font);
  g.drawFittedText("Machine0", 
                   text_x, text_y + 5.0,
                   text_width, title_size,
                   juce::Justification::centred, 1);

  g.setFont(info_font);
  g.setColour (default_text);
  g.drawFittedText("by",
                   text_x + text_width + 15.0, text_y + 12.0,
                   25.0, info_size,
                   juce::Justification::centred, 1);

  g.setColour (hl_text);
  g.drawFittedText("wolfink",
                   text_x + text_width + 40.0, text_y + 12.0,
                   70.0, info_size,
                   juce::Justification::centred, 1);

  g.setColour (default_text);
  std::stringstream version_string;
  version_string << "v" << PLUGIN_VERSION;
  g.drawFittedText(version_string.str(),
                   text_x + text_width + 110.0, text_y + 12.0,
                   70.0, info_size,
                   juce::Justification::centred, 1);
}

void MachZProcessorEditor::resized()
{
  auto area = getLocalBounds();
  auto margin  = 10.0;
  auto header  = 60.0;
  auto mix_pnl = 100.0;
  auto gen_pnl = 500.0;
  auto mod_pnl = 500.0;
  auto footer  = 80.0;

  area.removeFromTop(margin);
  area.removeFromBottom(margin);
  area.removeFromLeft(margin);
  area.removeFromRight(margin);

  area.removeFromTop(header);
  //area.removeFromBottom(footer);

  juce::FlexBox panel_flx;
  panel_flx.flexDirection = juce::FlexBox::Direction::column;
  panel_flx.alignItems = juce::FlexBox::AlignItems::center;
  panel_flx.items.add(juce::FlexItem(_oscPanel)
                      .withWidth(650)
                      .withFlex(1));
  panel_flx.items.add(juce::FlexItem(_genPanel)
                      .withWidth(650)
                      .withFlex(1));
  panel_flx.performLayout(area);

  // area.removeFromLeft(margin);
  // _mixPanel.setBounds(area.removeFromLeft(mix_pnl));
  // area.removeFromLeft(margin);
  // _genPanel.setBounds(area.removeFromLeft(gen_pnl));
  // area.removeFromLeft(margin);
  // _modPanel.setBounds(area.removeFromLeft(mod_pnl));
  // area.removeFromLeft(margin);
  // area.removeFromRight(margin);
  // _fxPanel.setBounds(area);
}

}
