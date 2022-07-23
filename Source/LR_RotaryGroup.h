/*
  ==============================================================================

    LR_RotaryGroup.h
    Created: 20 Jul 2022 11:00:37am
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RotaryPairWithLabel.h"

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
    // Slider pair with label
    RotaryPairWithLabel dryWetRPWL;
    RotaryPairWithLabel feedbackRPWL;
    RotaryPairWithLabel delayTimeRPWL;
    RotaryPairWithLabel cutoffLP_RPWL;
    RotaryPairWithLabel cutoffHP_RPWL;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_RotaryGroup)
};
