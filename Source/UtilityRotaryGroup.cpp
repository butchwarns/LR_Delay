/*
  ==============================================================================

    UtilityRotaryGroup.cpp
    Created: 19 Jul 2022 9:41:54pm
    Author:  butch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "UtilityRotaryGroup.h"
#include "ComponentSizeConstraints.h"

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
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    driveSlider.setTextValueSuffix(" dB");

    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    volumeSlider.setTextValueSuffix(" dB");

    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
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

    setupSliderAndLabel(volumeFB);
    setupSliderAndLabel(driveFB);
    setupSliderAndLabel(widthFB);

    //==============================================================================
    // Make FlexItems and add to box

    // Volume
    juce::FlexItem flexVolumeLabel = juce::FlexItem(volumeLabel)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_LABEL_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexVolumeSlider = juce::FlexItem(volumeSlider)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_HEIGHT)
                                        .withFlex(1.0f);

    volumeFB.items.add(flexVolumeLabel);
    volumeFB.items.add(flexVolumeSlider);

    // Drive
    juce::FlexItem flexDriveLabel = juce::FlexItem(driveLabel)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_LABEL_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexDriveSlider = juce::FlexItem(driveSlider)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_HEIGHT)
                                        .withFlex(1.0f);

    driveFB.items.add(flexDriveLabel);
    driveFB.items.add(flexDriveSlider);

    // Stereo width
    juce::FlexItem flexWidthLabel = juce::FlexItem(stereoWidthLabel)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_LABEL_HEIGHT)
                                        .withFlex(1.0f);

    juce::FlexItem flexWidthSlider = juce::FlexItem(stereoWidthSlider)
                                        .withMinWidth(MIN_ROTARY_WIDTH)
                                        .withMinHeight(MIN_SLIDER_HEIGHT)
                                        .withFlex(1.0f);

    widthFB.items.add(flexWidthLabel);
    widthFB.items.add(flexWidthSlider);

    //==============================================================================
    // Add to main FlexBox
    fb.items.add(FlexItem(volumeFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT + MIN_SLIDER_LABEL_HEIGHT));
    fb.items.add(FlexItem(driveFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT + MIN_SLIDER_LABEL_HEIGHT));
    fb.items.add(FlexItem(widthFB).withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_HEIGHT + MIN_SLIDER_LABEL_HEIGHT));

    fb.performLayout(getLocalBounds().toFloat());
}

//==============================================================================
// FlexBox helper
void UtilityRotaryGroup::setupSliderAndLabel(juce::FlexBox &fb)
{
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
}