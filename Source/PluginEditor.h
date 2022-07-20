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

    // Slider and labels
    juce::Slider dryWet_L_Slider;
    juce::Slider dryWet_R_Slider;
    juce::Label dryWet_L_Label;
    juce::Label dryWet_R_Label;

    juce::Slider feedback_L_Slider;
    juce::Slider feedback_R_Slider;
    juce::Label feedback_L_Label;
    juce::Label feedback_R_Label;

    juce::Slider delayTime_L_Slider;
    juce::Slider delayTime_R_Slider;
    juce::Label delayTime_L_Label;
    juce::Label delayTime_R_Label;

    juce::Slider cutoffLP_L_Slider;
    juce::Slider cutoffLP_R_Slider;
    juce::Label cutoffLP_L_Label;
    juce::Label cutoffLP_R_Label;

    juce::Slider cutoffHP_L_Slider;
    juce::Slider cutoffHP_R_Slider;
    juce::Label cutoffHP_L_Label;
    juce::Label cutoffHP_R_Label;

    //==============================================================================
    // Attachments to the parameters
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    std::unique_ptr<SliderAttachment> dryWet_L_Attachment;
    std::unique_ptr<SliderAttachment> dryWet_R_Attachment;

    std::unique_ptr<SliderAttachment> feedback_L_Attachment;
    std::unique_ptr<SliderAttachment> feedback_R_Attachment;

    std::unique_ptr<SliderAttachment> delayTime_L_Attachment;
    std::unique_ptr<SliderAttachment> delayTime_R_Attachment;

    std::unique_ptr<SliderAttachment> cutoffLP_L_Attachment;
    std::unique_ptr<SliderAttachment> cutoffLP_R_Attachment;

    std::unique_ptr<SliderAttachment> cutoffHP_L_Attachment;
    std::unique_ptr<SliderAttachment> cutoffHP_R_Attachment;

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
    const int width = 300;

    //==============================================================================
    // UI styling
    CustomLookAndFeel customLook;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_DelayAudioProcessorEditor)
};
