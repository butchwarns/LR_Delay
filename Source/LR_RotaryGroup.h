/*
  ==============================================================================

    LR_RotaryGroup.h
    Created: 20 Jul 2022 11:00:37am
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LR_RotaryGroup : public juce::Component
{
public:
    LR_RotaryGroup(juce::AudioProcessorValueTreeState &apvts);
    ~LR_RotaryGroup() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    //==============================================================================
    // Connection to paramter handling
    juce::AudioProcessorValueTreeState &apvts;

    //==============================================================================
    // Slider and labels
    juce::Slider dryWet_L_Slider;
    juce::Slider dryWet_R_Slider;

    juce::Label dryWetLabel;

    juce::Slider feedback_L_Slider;
    juce::Slider feedback_R_Slider;

    juce::Label feedbackLabel;

    juce::Slider delayTime_L_Slider;
    juce::Slider delayTime_R_Slider;

    juce::Label delayTimeLabel;

    juce::Slider cutoffLP_L_Slider;
    juce::Slider cutoffLP_R_Slider;

    juce::Label cutoffLP_Label;

    juce::Slider cutoffHP_L_Slider;
    juce::Slider cutoffHP_R_Slider;

    juce::Label cutoffHP_Label;

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

    //==============================================================================
    // FlexBox helpers
    static void setupSliderAndLabel(juce::FlexBox &fb);
    static void setupSliderPair(juce::FlexBox &fb);
    static void setupSliderPairAndLabel(juce::FlexBox &fb);

    juce::FlexItem makeFlexSlider(juce::Slider &s);
    juce::FlexItem makeFlexLabel(juce::Label &l);
    juce::FlexItem makeFlexPair(juce::FlexBox &pair);
    juce::FlexItem makeFlexPairAndLabel(juce::FlexBox &pairAndLabel);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_RotaryGroup)
};
