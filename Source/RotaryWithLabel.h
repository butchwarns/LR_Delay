/*
  ==============================================================================

    RotaryWithLabel.h
    Created: 21 Jul 2022 9:36:04am
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class RotaryWithLabel : public juce::Component
{
public:
    RotaryWithLabel();
    ~RotaryWithLabel() override;

    void paint(juce::Graphics &) override;
    void resized() override;

    //==============================================================================
    // UI components
    juce::Slider rotary;
    juce::Label label;

    //==============================================================================
    // Attachment to a parameter
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryWithLabel)
};
