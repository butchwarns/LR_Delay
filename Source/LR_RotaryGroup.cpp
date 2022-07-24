/*
  ==============================================================================

    LR_RotaryGroup.cpp
    Created: 20 Jul 2022 11:00:37am
    Author:  butch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LR_RotaryGroup.h"
#include "ComponentSizeConstraints.h"

//==============================================================================
LR_RotaryGroup::LR_RotaryGroup(juce::AudioProcessorValueTreeState &apvts) : apvts(apvts)
{
    //==============================================================================
    // Add and show all child components
    addAndMakeVisible(&dryWetRPWL);
    addAndMakeVisible(&feedbackRPWL);
    addAndMakeVisible(&delayTimeRPWL);
    addAndMakeVisible(&cutoffLP_RPWL);
    addAndMakeVisible(&cutoffHP_RPWL);

    //==============================================================================
    // Make all sliders rotary knobs
    typedef juce::Slider::SliderStyle SliderStyle;

    dryWetRPWL.rotary1.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    dryWetRPWL.rotary2.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    feedbackRPWL.rotary1.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    feedbackRPWL.rotary2.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    delayTimeRPWL.rotary1.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    delayTimeRPWL.rotary2.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    cutoffLP_RPWL.rotary1.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffLP_RPWL.rotary2.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    cutoffHP_RPWL.rotary1.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffHP_RPWL.rotary2.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    //==============================================================================
    // Make text boxes
    dryWetRPWL.rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    dryWetRPWL.rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    feedbackRPWL.rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    feedbackRPWL.rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    delayTimeRPWL.rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    delayTimeRPWL.rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    cutoffLP_RPWL.rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffLP_RPWL.rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    cutoffHP_RPWL.rotary1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffHP_RPWL.rotary2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);

    dryWetRPWL.rotary1.setTextValueSuffix(" %");
    dryWetRPWL.rotary2.setTextValueSuffix(" %");

    feedbackRPWL.rotary1.setTextValueSuffix(" %");
    feedbackRPWL.rotary2.setTextValueSuffix(" %");

    delayTimeRPWL.rotary1.setTextValueSuffix(" ms");
    delayTimeRPWL.rotary2.setTextValueSuffix(" ms");

    cutoffLP_RPWL.rotary1.setTextValueSuffix(" Hz");
    cutoffLP_RPWL.rotary2.setTextValueSuffix(" Hz");

    cutoffHP_RPWL.rotary1.setTextValueSuffix(" Hz");
    cutoffHP_RPWL.rotary2.setTextValueSuffix(" Hz");

    //==============================================================================
    // Label the sliders
    dryWetRPWL.label.setText("DRY / WET", juce::NotificationType::dontSendNotification);
    dryWetRPWL.label.setJustificationType(juce::Justification::centred);

    feedbackRPWL.label.setText("FEEDBACK", juce::NotificationType::dontSendNotification);
    feedbackRPWL.label.setJustificationType(juce::Justification::centred);

    delayTimeRPWL.label.setText("DELAY TIME", juce::NotificationType::dontSendNotification);
    delayTimeRPWL.label.setJustificationType(juce::Justification::centred);

    cutoffLP_RPWL.label.setText("LP CUTOFF", juce::NotificationType::dontSendNotification);
    cutoffLP_RPWL.label.setJustificationType(juce::Justification::centred);

    cutoffHP_RPWL.label.setText("HP CUTOFF", juce::NotificationType::dontSendNotification);
    cutoffHP_RPWL.label.setJustificationType(juce::Justification::centred);

    //==============================================================================
    // Attach parameters in processor to sliders
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    dryWetRPWL.sliderAttachment1.reset(new SliderAttachment(apvts, "dryWet_L", dryWetRPWL.rotary1));
    dryWetRPWL.sliderAttachment2.reset(new SliderAttachment(apvts, "dryWet_R", dryWetRPWL.rotary2));

    feedbackRPWL.sliderAttachment1.reset(new SliderAttachment(apvts, "feedback_L", feedbackRPWL.rotary1));
    feedbackRPWL.sliderAttachment2.reset(new SliderAttachment(apvts, "feedback_R", feedbackRPWL.rotary2));

    delayTimeRPWL.sliderAttachment1.reset(new SliderAttachment(apvts, "delayTime_L", delayTimeRPWL.rotary1));
    delayTimeRPWL.sliderAttachment2.reset(new SliderAttachment(apvts, "delayTime_R", delayTimeRPWL.rotary2));

    cutoffLP_RPWL.sliderAttachment1.reset(new SliderAttachment(apvts, "cutoffLP_L", cutoffLP_RPWL.rotary1));
    cutoffLP_RPWL.sliderAttachment2.reset(new SliderAttachment(apvts, "cutoffLP_R", cutoffLP_RPWL.rotary2));

    cutoffHP_RPWL.sliderAttachment1.reset(new SliderAttachment(apvts, "cutoffHP_L", cutoffHP_RPWL.rotary1));
    cutoffHP_RPWL.sliderAttachment2.reset(new SliderAttachment(apvts, "cutoffHP_R", cutoffHP_RPWL.rotary2));
}

LR_RotaryGroup::~LR_RotaryGroup() {}

void LR_RotaryGroup::paint(juce::Graphics &g) 
{
    // g.setColour(juce::Colours::white);
    // g.drawRect(getLocalBounds());
}

void LR_RotaryGroup::resized()
{
    typedef juce::FlexItem FlexItem;
    typedef juce::FlexBox FlexBox;

    //==============================================================================
    // Stack all pairs vertically
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    fb.alignItems = FlexBox::AlignItems::center;
    fb.flexWrap = FlexBox::Wrap::noWrap;

    //=============================================================================
    // Make flexitems to add to the box
    FlexItem flexDryWetRPWL(dryWetRPWL);
    FlexItem flexFeedbackRPWL(feedbackRPWL);
    FlexItem flexDelayTimeRPWL(delayTimeRPWL);
    FlexItem flexCutoffLP_RPWL(cutoffLP_RPWL);
    FlexItem flexCutoffHP_RPWL(cutoffHP_RPWL);

    flexDryWetRPWL = flexDryWetRPWL.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexFeedbackRPWL = flexFeedbackRPWL.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexDelayTimeRPWL = flexDelayTimeRPWL.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexCutoffLP_RPWL = flexCutoffLP_RPWL.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);
    flexCutoffHP_RPWL = flexCutoffHP_RPWL.withMinWidth(2 * MIN_ROTARY_WIDTH).withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT);

    //==============================================================================
    // Add to box and layout
    fb.items.add(flexDryWetRPWL, flexFeedbackRPWL, flexDelayTimeRPWL, flexCutoffLP_RPWL, flexCutoffHP_RPWL); fb.performLayout(getLocalBounds());
}