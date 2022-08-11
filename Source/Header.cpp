/*
  ==============================================================================

    Header.cpp

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
#include "Header.h"

//==============================================================================
Header::Header()
{
    //==============================================================================
    // Add children
    addChildComponent(titleLabel);
    addChildComponent(versionLabel);

    //==============================================================================
    // Setup Labels
    titleLabel.setText("LR_DELAY", juce::NotificationType::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::left);

    versionLabel.setText("V0.1.0", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::right);

    //==============================================================================
    // Make components visible
    addAndMakeVisible(&titleLabel);
    addAndMakeVisible(&versionLabel);
}

Header::~Header()
{
}

void Header::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void Header::resized()
{
    //==============================================================================
    const int width = getLocalBounds().getWidth();
    const int height = getLocalBounds().getHeight();

    //==============================================================================
    typedef juce::FlexBox FlexBox;

    FlexBox fb;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::spaceBetween;
    fb.alignItems = FlexBox::AlignItems::center;

    juce::FlexItem flexTitleLabel = juce::FlexItem(titleLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.75f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexVersionLabel = juce::FlexItem(versionLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.25f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    fb.items.add(flexTitleLabel);
    fb.items.add(flexVersionLabel);

    fb.performLayout(getLocalBounds());
}