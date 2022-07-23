/*
  ==============================================================================

    RotaryPairWithLabel.cpp
    Created: 23 Jul 2022 10:36:48am
    Author:  butch

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
    // FlexBox to stack rotary and label vertically
    typedef juce::FlexBox FB;
    FB fb;
    fb.flexDirection = FB::Direction::column;
    fb.justifyContent = FB::JustifyContent::flexEnd;
    fb.alignItems = FB::AlignItems::center;
    fb.alignContent = FB::AlignContent::center;
    fb.flexWrap = FB::Wrap::wrap;

    // Make FlexItems
    typedef juce::FlexItem FI;
    FI flexSlider1(rotary1);
    FI flexSlider2(rotary2);
    FI flexLabel(label);

    flexSlider1 = flexSlider1.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);
    flexSlider2 = flexSlider2.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT);

    flexSlider1 = flexSlider1.withFlex(8.0f, 0.0f, 0.0f);
    flexSlider2 = flexSlider2.withFlex(8.0f, 0.0f, 0.0f);

    flexLabel = flexLabel.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_LABEL_HEIGHT);
    flexLabel = flexLabel.withFlex(2.0f, 0.0f, 0.0f).withAlignSelf(FI::AlignSelf::center);

    // Add to the box
    fb.items.add(flexLabel, flexSlider1, flexSlider2);

    // Layout!
    fb.performLayout(getLocalBounds());
}
