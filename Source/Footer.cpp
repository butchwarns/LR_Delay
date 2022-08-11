/*
  ==============================================================================

    Footer.cpp

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
#include "Footer.h"

//==============================================================================
Footer::Footer()
{
    //==============================================================================
    // Add children
    addChildComponent(coprLabel);
    addChildComponent(websiteLabel);

    //==============================================================================
    // Setup Labels
    coprLabel.setText("2022", juce::NotificationType::dontSendNotification);
    coprLabel.setJustificationType(juce::Justification::left);

    websiteLabel.setText("BUTCHWARNS.DE", juce::NotificationType::dontSendNotification);
    websiteLabel.setJustificationType(juce::Justification::right);

    //==============================================================================
    // Make components visible
    addAndMakeVisible(&coprLabel);
    addAndMakeVisible(&websiteLabel);
}

Footer::~Footer()
{
}

void Footer::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void Footer::resized()
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

    juce::FlexItem flexCoprLabel = juce::FlexItem(coprLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.25f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexWebsiteLabel = juce::FlexItem(websiteLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.75f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    fb.items.add(flexCoprLabel);
    fb.items.add(flexWebsiteLabel);

    fb.performLayout(getLocalBounds());
}
