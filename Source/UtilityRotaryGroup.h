/*
  ==============================================================================

    UtilityRotaryGroup.h
    Created: 19 Jul 2022 9:41:54pm
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class UtilityRotaryGroup : public juce::Component
{
public:
    UtilityRotaryGroup(juce::AudioProcessorValueTreeState &apvts);
    ~UtilityRotaryGroup() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState &apvts;

    //==============================================================================
    // Sliders and their labels
    juce::Slider driveSlider;
    juce::Label driveLabel;

    juce::Slider volumeSlider;
    juce::Label volumeLabel;

    juce::Slider stereoWidthSlider;
    juce::Label stereoWidthLabel;

    //==============================================================================
    // Attachments to the parameters
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<SliderAttachment> stereoWidthAttachment;

    //==============================================================================
    // FlexBox helpers
    static void setupSliderAndLabel(juce::FlexBox &fb);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityRotaryGroup)
};
