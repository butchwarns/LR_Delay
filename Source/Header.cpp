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
    versionLabel.setText("VERSION: 0.1.0", juce::NotificationType::dontSendNotification);
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g){}

void Header::resized()
{
    typedef juce::FlexBox FlexBox;
    FlexBox fb;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::center;
    fb.alignContent = FlexBox::AlignContent::center;

    fb.items.add(juce::FlexItem(titleLabel));
    fb.items.add(juce::FlexItem(versionLabel));

    fb.performLayout(getLocalBounds().toFloat());
}
