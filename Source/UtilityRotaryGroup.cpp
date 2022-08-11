/*
  ==============================================================================

    UtilityRotaryGroup.cpp

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
#include "UtilityRotaryGroup.h"

//==============================================================================
UtilityRotaryGroup::UtilityRotaryGroup(juce::AudioProcessorValueTreeState &apvts) : apvts(apvts)
{
    //==============================================================================
    // Add and show children
    addAndMakeVisible(&volumeRWL);
    addAndMakeVisible(&driveRWL);
    addAndMakeVisible(&stereoWidthRWL);

    //==============================================================================
    // Setup slider text boxes
    volumeRWL.rotary.setTextValueSuffix(" dB");
    driveRWL.rotary.setTextValueSuffix(" dB");
    stereoWidthRWL.rotary.setTextValueSuffix(" %");

    //==============================================================================
    // Label the sliders
    volumeRWL.label.setText("VOLUME", juce::NotificationType::dontSendNotification);
    driveRWL.label.setText("DRIVE", juce::NotificationType::dontSendNotification);
    stereoWidthRWL.label.setText("WIDTH", juce::NotificationType::dontSendNotification);

    //==============================================================================
    // Attach sliders to parameters
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    volumeRWL.sliderAttachment.reset(new SliderAttachment(apvts, "volume", volumeRWL.rotary));
    driveRWL.sliderAttachment.reset(new SliderAttachment(apvts, "drive", driveRWL.rotary));
    stereoWidthRWL.sliderAttachment.reset(new SliderAttachment(apvts, "stereoWidth", stereoWidthRWL.rotary));
}

UtilityRotaryGroup::~UtilityRotaryGroup() {}

void UtilityRotaryGroup::paint(juce::Graphics &g)
{
    // g.setColour(juce::Colours::white);
    // g.drawRect(getLocalBounds());
}

void UtilityRotaryGroup::resized()
{
    // Stack all sliders vertically
    typedef juce::FlexBox FlexBox;
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.alignItems = FlexBox::AlignItems::center;
    fb.flexWrap = FlexBox::Wrap::noWrap;

    //==============================================================================
    // FlexItems for the box
    typedef juce::FlexItem FlexItem;
    FlexItem flexVolumeRWL(volumeRWL);
    FlexItem flexDriveRWL(driveRWL);
    FlexItem flexStereoWidthRWL(stereoWidthRWL);

    flexVolumeRWL = flexVolumeRWL.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexDriveRWL = flexDriveRWL.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexStereoWidthRWL = flexStereoWidthRWL.withMinWidth(MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);

    //==============================================================================
    // Add to FlexBox and layout
    fb.items.add(flexVolumeRWL, flexDriveRWL, flexStereoWidthRWL);

    fb.performLayout(getLocalBounds());
}