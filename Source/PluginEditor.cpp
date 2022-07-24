/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessorEditor::LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p), rotaryGroupLR(p.getApvts()), utilityRotaryGroup(p.getApvts())
{
    // Set main window size behaviour
    setResizable(true, true);
    const int minWidth = MIN_UTIL_WIDTH + MIN_LR_WIDTH;
    const int minHeight = MIN_HEADER_HEIGHT + MIN_FOOTER_HEIGHT + 5 * MIN_SLIDER_WITH_LABEL_HEIGHT;

    const juce::Rectangle<int> screenBounds = juce::Desktop::getInstance().getDisplays().getDisplayForPoint(juce::Point<int>(0, 0))->userArea;
    const int screenWidth = screenBounds.getWidth();
    const int screenHeight = screenBounds.getHeight();
    setResizeLimits(minWidth, minHeight, screenWidth, screenHeight);

    setSize(minWidth, minHeight);

    //==============================================================================
    // Add as children and show all components
    addAndMakeVisible(&header);
    addAndMakeVisible(&footer);

    addAndMakeVisible(&utilityRotaryGroup);
    addAndMakeVisible(&rotaryGroupLR);

    //==============================================================================
    // Set "global" look and feel
    setLookAndFeel(&customLook);
}

LR_DelayAudioProcessorEditor::~LR_DelayAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void LR_DelayAudioProcessorEditor::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void LR_DelayAudioProcessorEditor::resized()
{
    typedef juce::Rectangle<int> Rect;

    // Local bounds
    Rect localBounds = getLocalBounds();
    juce::Rectangle<float> localBoundsFloat = localBounds.toFloat();
    const float width = localBoundsFloat.getWidth();
    const float height = localBoundsFloat.getHeight();

    // Layout header and footer
    const int headerHeight = juce::jmax(static_cast<int>(0.02f * height), MIN_HEADER_HEIGHT);
    const int footerHeight = juce::jmax(static_cast<int>(0.02f * height), MIN_FOOTER_HEIGHT);

    Rect headerArea = localBounds.removeFromTop(headerHeight);
    Rect footerArea = localBounds.removeFromBottom(footerHeight);

    // Layout utility area (minimum size)
    // const int utilWidth = juce::jmax(static_cast<int>(width * (1.0f - 1.0f / PHI)), MIN_UTIL_WIDTH);
    const int utilWidth = juce::jmax(MIN_UTIL_WIDTH, static_cast<int>(width / 3.0f));
    Rect utilArea = localBounds.removeFromLeft(utilWidth);
    Rect &rotaryLRArea = localBounds;

    // Layout main area (minimum size)
    localBounds.setWidth(juce::jmax(localBounds.getWidth(), MIN_LR_WIDTH));

    //==============================================================================
    // Set bounds
    header.setBounds(headerArea);
    footer.setBounds(footerArea);

    utilityRotaryGroup.setBounds(utilArea);
    rotaryGroupLR.setBounds(rotaryLRArea);
}
