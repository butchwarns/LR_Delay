/*
  ==============================================================================

    RotaryWithLabel.cpp

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
#include "RotaryWithLabel.h"
#include "ComponentSizeConstraints.h"

//==============================================================================
RotaryWithLabel::RotaryWithLabel()
{
    // Add children and show them
    addAndMakeVisible(&rotary);
    addAndMakeVisible(&label);

    // Setup rotary slider with text box
    rotary.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    rotary.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    // Setup label
    label.setJustificationType(juce::Justification::centred);

    // The rest is setup from outside the class accessing the public member components
}

RotaryWithLabel::~RotaryWithLabel()
{
}

void RotaryWithLabel::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void RotaryWithLabel::resized()
{
    // FlexBox to stack rotary and label vertically
    typedef juce::FlexBox FB;
    FB fb;
    fb.flexDirection = FB::Direction::column;
    fb.justifyContent = FB::JustifyContent::center;
    fb.alignItems = FB::AlignItems::center;
    fb.flexWrap = FB::Wrap::noWrap;

    // Make FlexItems
    typedef juce::FlexItem FI;
    FI flexSlider(rotary);
    FI flexLabel(label);

    flexSlider = flexSlider.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);
    flexSlider = flexSlider.withFlex(8.0f);

    flexLabel = flexLabel.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_LABEL_HEIGHT);
    flexLabel = flexLabel.withFlex(2.0f);

    // Add to the box
    fb.items.add(flexLabel, flexSlider);

    // Layout!
    fb.performLayout(getLocalBounds());
}
