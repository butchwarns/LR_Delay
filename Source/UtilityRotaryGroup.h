/*
  ==============================================================================

    UtilityRotaryGroup.h
    Created: 19 Jul 2022 9:41:54pm
    Author:  butch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ComponentSizeConstraints.h"
#include "RotaryWithLabel.h"

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
    RotaryWithLabel volumeRWL;
    RotaryWithLabel driveRWL;
    RotaryWithLabel stereoWidthRWL;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityRotaryGroup)
};
