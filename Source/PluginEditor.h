/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "Header.h"
#include "Footer.h"
#include "UtilityRotaryGroup.h"
#include "LR_RotaryGroup.h"

//==============================================================================
/**
 */
class LR_DelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts);
    ~LR_DelayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LR_DelayAudioProcessor &audioProcessor;

    //==============================================================================
    // UI elements

    Header header;
    Footer footer;

    UtilityRotaryGroup utilityRotaryGroup;
    LR_RotaryGroup rotaryGroupLR;

    //==============================================================================f
    // Reference to the AudioProcessorValueTreeState object in the Processor
    juce::AudioProcessorValueTreeState &apvts;

    //==============================================================================
    // Magic numbers for UI layout
    const int rotaryWidth = 80;
    const int textBoxHeight = 25;
    const int rotaryHeight = 80 + textBoxHeight;

    const int HEADER_HEIGHT = 50;
    const int FOOTER_HEIGHT = 50;

    const int labelHeight = 25;

    const int roLaHeight = rotaryHeight + labelHeight;

    const int rotaryCols = 3;
    const int rotaryRows = 5;

    const int height = HEADER_HEIGHT + FOOTER_HEIGHT + (rotaryRows * roLaHeight);
    const int width = 400;

    //==============================================================================
    // UI styling
    CustomLookAndFeel customLook;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_DelayAudioProcessorEditor)
};
