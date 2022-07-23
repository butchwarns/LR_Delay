/*
  ==============================================================================

    Footer.cpp
    Created: 19 Jul 2022 8:18:10pm
    Author:  butch

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
                                        .withMinWidth(static_cast<float>(width) * 0.5f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexWebsiteLabel = juce::FlexItem(websiteLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.5f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    fb.items.add(flexCoprLabel);
    fb.items.add(flexWebsiteLabel);

    fb.performLayout(getLocalBounds());
}
