/*
  ==============================================================================

    RotaryPairWithLabel.cpp

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

#include <JuceHeader.h>
#include "RotaryPairWithLabel.h"

//==============================================================================
RotaryPairWithLabel::RotaryPairWithLabel()
{
    // Add children and show them
    addAndMakeVisible(&rotary1);
    addAndMakeVisible(&rotary2);
    addAndMakeVisible(&label);

    // Setup rotary sliders with text box
    rotary1.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    rotary2.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    // Setup label
    label.setJustificationType(juce::Justification::centred);

    // The rest is setup from outside the class accessing the public member components
}

RotaryPairWithLabel::~RotaryPairWithLabel()
{
}

void RotaryPairWithLabel::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void RotaryPairWithLabel::resized()
{
    //==============================================================================
    // FlexBox to stack rotary pair and label vertically
    typedef juce::FlexBox FB;
    FB fb;
    fb.flexDirection = FB::Direction::column;
    fb.justifyContent = FB::JustifyContent::center;
    fb.alignItems = FB::AlignItems::center;
    fb.alignContent = FB::AlignContent::center;
    fb.flexWrap = FB::Wrap::noWrap;

    // FlexBox to stack the two rotaries horizontally
    FB pairFB;
    pairFB.flexDirection = FB::Direction::row;
    pairFB.justifyContent = FB::JustifyContent::center;
    pairFB.alignItems = FB::AlignItems::center;
    pairFB.flexWrap = FB::Wrap::noWrap;

    //==============================================================================
    // Make FlexItems
    typedef juce::FlexItem FI;
    FI flexSlider1(rotary1);
    FI flexSlider2(rotary2);
    FI flexLabel(label);

    flexSlider1 = flexSlider1.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);
    flexSlider2 = flexSlider2.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);

    flexSlider1 = flexSlider1.withFlex(8.0f, 0.0f, 0.0f);
    flexSlider2 = flexSlider2.withFlex(8.0f, 0.0f, 0.0f);

    flexLabel = flexLabel.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_LABEL_HEIGHT);
    flexLabel = flexLabel.withFlex(2.0f, 0.0f, 0.0f).withAlignSelf(FI::AlignSelf::center);

    // Make flex rotary pair
    pairFB.items.add(flexSlider1, flexSlider2);

    FI flexPairFB(pairFB);
    flexPairFB = flexPairFB.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);

    // Add to the box
    fb.items.add(flexLabel, flexPairFB);

    // Layout!
    fb.performLayout(getLocalBounds());
}
