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
    // Set main window size
    setSize(400, 900);
    setResizable(true, true);

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
}

void LR_DelayAudioProcessorEditor::resized()
{
    typedef juce::Rectangle<int> Rect;
    Rect localBounds = getLocalBounds();

    Rect headerArea = localBounds.removeFromTop(HEADER_HEIGHT);
    Rect footerArea = localBounds.removeFromBottom(FOOTER_HEIGHT);
    Rect utilArea = localBounds.removeFromLeft(100);
    Rect &rotaryLRArea = localBounds;

    // Add padding
    headerArea.reduce(PAD, PAD);
    footerArea.reduce(PAD, PAD);
    utilArea.reduce(PAD, PAD);
    rotaryLRArea.reduce(PAD, PAD);

    //==============================================================================
    // Set bounds
    header.setBounds(headerArea);
    footer.setBounds(footerArea);

    utilityRotaryGroup.setBounds(utilArea);
    rotaryGroupLR.setBounds(rotaryLRArea);
}
