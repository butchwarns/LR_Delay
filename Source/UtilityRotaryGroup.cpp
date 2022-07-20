/*
  ==============================================================================

    UtilityRotaryGroup.cpp
    Created: 19 Jul 2022 9:41:54pm
    Author:  butch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "UtilityRotaryGroup.h"

//==============================================================================
UtilityRotaryGroup::UtilityRotaryGroup(juce::AudioProcessorValueTreeState &apvts) : apvts(apvts)
{
    //==============================================================================
    // Add and show children
    addAndMakeVisible(&driveSlider);
    addAndMakeVisible(&driveLabel);

    addAndMakeVisible(&volumeSlider);
    addAndMakeVisible(&volumeLabel);

    addAndMakeVisible(&stereoWidthSlider);
    addAndMakeVisible(&stereoWidthLabel);

    //==============================================================================
    // Make rotary sliders
    driveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    volumeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    stereoWidthSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    //==============================================================================
    // Setup slider text boxes
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    driveSlider.setTextValueSuffix(" dB");

    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    volumeSlider.setTextValueSuffix(" dB");

    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    stereoWidthSlider.setTextValueSuffix(" %");

    //==============================================================================
    // Label the sliders
    driveLabel.setText("DRIVE", juce::NotificationType::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);

    volumeLabel.setText("VOLUME", juce::NotificationType::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred);

    stereoWidthLabel.setText("WIDTH", juce::NotificationType::dontSendNotification);
    stereoWidthLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================
    // Attach sliders to parameters
    driveAttachment.reset(new SliderAttachment(apvts, "drive", driveSlider));
    volumeAttachment.reset(new SliderAttachment(apvts, "volume", volumeSlider));
    stereoWidthAttachment.reset(new SliderAttachment(apvts, "stereoWidth", stereoWidthSlider));
}

UtilityRotaryGroup::~UtilityRotaryGroup() {}

void UtilityRotaryGroup::paint(juce::Graphics &g){}

void UtilityRotaryGroup::resized()
{
    typedef juce::FlexItem FlexItem;
    typedef juce::FlexBox FlexBox;

    const int sliderHeight = MIN_ROTARY_HEIGHT + MIN_TEXTBOX_HEIGHT;

    // Stack all sliders vertically
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.alignItems = FlexBox::AlignItems::center;
    fb.flexWrap = FlexBox::Wrap::noWrap;

    //=============================================================================
    // FlexBoxes for rotary with label
    FlexBox volumeFB;
    FlexBox driveFB;
    FlexBox widthFB;

    volumeFB.flexDirection = FlexBox::Direction::column;
    driveFB.flexDirection = FlexBox::Direction::column;
    widthFB.flexDirection = FlexBox::Direction::column;

    volumeFB.justifyContent = FlexBox::JustifyContent::center;
    driveFB.justifyContent = FlexBox::JustifyContent::center;
    widthFB.justifyContent = FlexBox::JustifyContent::center;

    volumeFB.alignItems = FlexBox::AlignItems::center;
    driveFB.alignItems = FlexBox::AlignItems::center;
    widthFB.alignItems = FlexBox::AlignItems::center;

    volumeFB.flexWrap = FlexBox::Wrap::noWrap;
    driveFB.flexWrap = FlexBox::Wrap::noWrap;
    widthFB.flexWrap = FlexBox::Wrap::noWrap;

    volumeFB.items.add(FlexItem(volumeLabel).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    volumeFB.items.add(FlexItem(volumeSlider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    driveFB.items.add(FlexItem(driveLabel).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    driveFB.items.add(FlexItem(driveSlider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    widthFB.items.add(FlexItem(stereoWidthLabel).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    widthFB.items.add(FlexItem(stereoWidthSlider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    // Add to main FlexBox
    fb.items.add(FlexItem(volumeFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(driveFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(widthFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));

    fb.performLayout(getLocalBounds().toFloat());
}
