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

    versionLabel.setText("VERSION 0.1.0", juce::NotificationType::dontSendNotification);

    //==============================================================================
    // Make components visible
    addAndMakeVisible(&titleLabel);
    addAndMakeVisible(&versionLabel);
}

Header::~Header()
{
}

void Header::paint(juce::Graphics &g) {}

void Header::resized()
{
    typedef juce::FlexBox FlexBox;
    FlexBox fb;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.justifyContent = FlexBox::JustifyContent::spaceBetween;

    fb.items.add(juce::FlexItem(titleLabel).withMinWidth(MIN_LABEL_WIDTH).withMinHeight(MIN_LABEL_HEIGHT));
    fb.items.add(juce::FlexItem(versionLabel).withMinWidth(MIN_LABEL_WIDTH).withMinHeight(MIN_LABEL_HEIGHT).withMaxHeight(MAX_HEIGHT));

    fb.performLayout(getLocalBounds().toFloat());
}
