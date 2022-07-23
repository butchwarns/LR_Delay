/*
  ==============================================================================

    RotaryPairWithLabel.h
    Created: 23 Jul 2022 10:36:48am
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ComponentSizeConstraints.h"

//==============================================================================
/*
*/
class RotaryPairWithLabel  : public juce::Component
{
public:
    RotaryPairWithLabel();
    ~RotaryPairWithLabel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    // UI components
    juce::Slider rotary1;
    juce::Slider rotary2;
    juce::Label label;

    //==============================================================================
    // Attachment to a parameter
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment1;
    std::unique_ptr<SliderAttachment> sliderAttachment2;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryPairWithLabel)
};
