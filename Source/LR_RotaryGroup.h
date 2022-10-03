/*
  ==============================================================================

    LR_RotaryGroup.h

    Copyright (C) 2022 Butch Warns
    contact@butchwarns.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    RotaryPairWithLabel preDelayRPWL;
    RotaryPairWithLabel cutoffLP_RPWL;
    RotaryPairWithLabel cutoffHP_RPWL;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_RotaryGroup)
};
