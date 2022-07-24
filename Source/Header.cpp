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
                                        .withMinWidth(static_cast<float>(width) * 0.5f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexVersionLabel = juce::FlexItem(versionLabel)
                                        .withMinWidth(static_cast<float>(width) * 0.5f)
                                        .withMinHeight(MIN_HEADER_HEIGHT)
                                        .withFlex(1.0f);

    fb.items.add(flexTitleLabel);
    fb.items.add(flexVersionLabel);

    fb.performLayout(getLocalBounds());
}