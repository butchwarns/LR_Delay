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
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
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

    fb.items.add(juce::FlexItem(titleLabel).withMinWidth(static_cast<float>(width) * 0.5f).withMinHeight(MIN_LABEL_HEIGHT));
    fb.items.add(juce::FlexItem(versionLabel).withMinWidth(static_cast<float>(width) * 0.5f).withMinHeight(MIN_LABEL_HEIGHT).withMaxHeight(MAX_HEIGHT));

    fb.performLayout(getLocalBounds().toFloat());
}
