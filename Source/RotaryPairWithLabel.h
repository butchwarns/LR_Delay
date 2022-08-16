/*
  ==============================================================================

    RotaryPairWithLabel.h

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
