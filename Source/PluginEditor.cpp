/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessorEditor::LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts)
    : AudioProcessorEditor(&p), audioProcessor(p), apvts(apvts), utilityRotaryGroup(apvts), rotaryGroupLR(apvts)
{
    // Set main window size
    setSize(width, height);

    //==============================================================================
    // Add children
    addChildComponent(header);
    addChildComponent(footer);

    addChildComponent(utilityRotaryGroup);
    addChildComponent(rotaryGroupLR);

    //==============================================================================
    // Set "global" look and feel
    setLookAndFeel(&customLook);

    //==============================================================================
    // Show all components
    addAndMakeVisible(&header);
    addAndMakeVisible(&footer);

    addAndMakeVisible(&utilityRotaryGroup);
    addAndMakeVisible(&rotaryGroupLR);
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

    //==============================================================================
    // Header & footer

    header.setBounds(headerArea);
    footer.setBounds(footerArea);

    utilityRotaryGroup.setBounds(utilArea);
    rotaryGroupLR.setBounds(rotaryLRArea);

    //==============================================================================
    // Slider and their labels
    // dryWet_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 0 * roLaHeight, rotaryWidth, labelHeight);
    // dryWet_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 0 * roLaHeight, rotaryWidth, labelHeight);

    // dryWet_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);
    // dryWet_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);

    // feedback_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 1 * roLaHeight, rotaryWidth, labelHeight);
    // feedback_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 1 * roLaHeight, rotaryWidth, labelHeight);

    // feedback_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);
    // feedback_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);

    // delayTime_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 2 * roLaHeight, rotaryWidth, labelHeight);
    // delayTime_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 2 * roLaHeight, rotaryWidth, labelHeight);

    // delayTime_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);
    // delayTime_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);

    // cutoffLP_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 3 * roLaHeight, rotaryWidth, labelHeight);
    // cutoffLP_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 3 * roLaHeight, rotaryWidth, labelHeight);

    // cutoffLP_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);
    // cutoffLP_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);

    // cutoffHP_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 4 * roLaHeight, rotaryWidth, labelHeight);
    // cutoffHP_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 4 * roLaHeight, rotaryWidth, labelHeight);

    // cutoffHP_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);
    // cutoffHP_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);
}
