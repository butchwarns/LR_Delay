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
    const juce::AudioProcessorValueTreeState &apvts;

    //==============================================================================
    // Attachments to the parameters
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<SliderAttachment> stereoWidthAttachment;

    //==============================================================================
    // Magic numbers for layout
    const int MIN_LABEL_HEIGHT = 25;

    const int MIN_ROTARY_WIDTH = 80;
    const int MIN_ROTARY_HEIGHT = MIN_ROTARY_WIDTH;

    const int MIN_TEXTBOX_HEIGHT = 25;

    //==============================================================================
    // Sliders and their labels
    juce::Slider driveSlider;
    juce::Label driveLabel;

    juce::Slider volumeSlider;
    juce::Label volumeLabel;

    juce::Slider stereoWidthSlider;
    juce::Label stereoWidthLabel;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityRotaryGroup)
};
