/*
  ==============================================================================

    LR_RotaryGroup.cpp
    Created: 20 Jul 2022 11:00:37am
    Author:  butch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LR_RotaryGroup.h"

//==============================================================================
LR_RotaryGroup::LR_RotaryGroup(juce::AudioProcessorValueTreeState &apvts) : apvts(apvts)
{
    //==============================================================================
    // Add and show all child components
    addAndMakeVisible(&dryWet_L_Slider);
    addAndMakeVisible(&dryWet_R_Slider);
    addAndMakeVisible(&dryWet_L_Label);
    addAndMakeVisible(&dryWet_R_Label);

    addAndMakeVisible(&feedback_L_Slider);
    addAndMakeVisible(&feedback_R_Slider);
    addAndMakeVisible(&feedback_L_Label);
    addAndMakeVisible(&feedback_R_Label);

    addAndMakeVisible(&delayTime_L_Slider);
    addAndMakeVisible(&delayTime_R_Slider);
    addAndMakeVisible(&delayTime_L_Label);
    addAndMakeVisible(&delayTime_R_Label);

    addAndMakeVisible(&cutoffLP_L_Slider);
    addAndMakeVisible(&cutoffLP_R_Slider);
    addAndMakeVisible(&cutoffLP_L_Label);
    addAndMakeVisible(&cutoffLP_R_Label);

    addAndMakeVisible(&cutoffHP_L_Slider);
    addAndMakeVisible(&cutoffHP_R_Slider);
    addAndMakeVisible(&cutoffHP_L_Label);
    addAndMakeVisible(&cutoffHP_R_Label);

    //==============================================================================
    // Make all sliders rotary knobs
    typedef juce::Slider::SliderStyle SliderStyle;

    dryWet_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    dryWet_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    feedback_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    feedback_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    delayTime_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    delayTime_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    cutoffLP_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffLP_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    cutoffHP_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffHP_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);

    //==============================================================================
    // Make text boxes
    dryWet_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    dryWet_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    dryWet_L_Slider.setTextValueSuffix(" %");
    dryWet_R_Slider.setTextValueSuffix(" %");

    feedback_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    feedback_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    feedback_L_Slider.setTextValueSuffix(" %");
    feedback_R_Slider.setTextValueSuffix(" %");

    delayTime_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    delayTime_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    delayTime_L_Slider.setTextValueSuffix(" ms");
    delayTime_R_Slider.setTextValueSuffix(" ms");

    cutoffLP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    cutoffLP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    cutoffLP_L_Slider.setTextValueSuffix(" Hz");
    cutoffLP_R_Slider.setTextValueSuffix(" Hz");

    cutoffHP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    cutoffHP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_TEXTBOX_HEIGHT);
    cutoffHP_L_Slider.setTextValueSuffix(" Hz");
    cutoffHP_R_Slider.setTextValueSuffix(" Hz");

    //==============================================================================
    // Label the sliders
    dryWet_L_Label.setText("DRY/WET L", juce::NotificationType::dontSendNotification);
    dryWet_L_Label.setJustificationType(juce::Justification::centred);
    dryWet_R_Label.setText("DRY/WET R", juce::NotificationType::dontSendNotification);
    dryWet_R_Label.setJustificationType(juce::Justification::centred);

    feedback_L_Label.setText("FDBK L", juce::NotificationType::dontSendNotification);
    feedback_L_Label.setJustificationType(juce::Justification::centred);
    feedback_R_Label.setText("FDBK R", juce::NotificationType::dontSendNotification);
    feedback_R_Label.setJustificationType(juce::Justification::centred);

    delayTime_L_Label.setText("TIME L", juce::NotificationType::dontSendNotification);
    delayTime_L_Label.setJustificationType(juce::Justification::centred);
    delayTime_R_Label.setText("TIME R", juce::NotificationType::dontSendNotification);
    delayTime_R_Label.setJustificationType(juce::Justification::centred);

    cutoffLP_L_Label.setText("LP L", juce::NotificationType::dontSendNotification);
    cutoffLP_L_Label.setJustificationType(juce::Justification::centred);
    cutoffLP_R_Label.setText("LP R", juce::NotificationType::dontSendNotification);
    cutoffLP_R_Label.setJustificationType(juce::Justification::centred);

    cutoffHP_L_Label.setText("HP L", juce::NotificationType::dontSendNotification);
    cutoffHP_L_Label.setJustificationType(juce::Justification::centred);
    cutoffHP_R_Label.setText("HP R", juce::NotificationType::dontSendNotification);
    cutoffHP_R_Label.setJustificationType(juce::Justification::centred);

    //==============================================================================
    // Attach parameters in processor to sliders
    dryWet_L_Attachment.reset(new SliderAttachment(apvts, "dryWet_L", dryWet_L_Slider));
    dryWet_R_Attachment.reset(new SliderAttachment(apvts, "dryWet_R", dryWet_R_Slider));

    feedback_L_Attachment.reset(new SliderAttachment(apvts, "feedback_L", feedback_L_Slider));
    feedback_R_Attachment.reset(new SliderAttachment(apvts, "feedback_R", feedback_R_Slider));

    delayTime_L_Attachment.reset(new SliderAttachment(apvts, "delayTime_L", delayTime_L_Slider));
    delayTime_R_Attachment.reset(new SliderAttachment(apvts, "delayTime_R", delayTime_R_Slider));

    cutoffLP_L_Attachment.reset(new SliderAttachment(apvts, "cutoffLP_L", cutoffLP_L_Slider));
    cutoffLP_R_Attachment.reset(new SliderAttachment(apvts, "cutoffLP_R", cutoffLP_R_Slider));

    cutoffHP_L_Attachment.reset(new SliderAttachment(apvts, "cutoffHP_L", cutoffHP_L_Slider));
    cutoffHP_R_Attachment.reset(new SliderAttachment(apvts, "cutoffHP_R", cutoffHP_R_Slider));
}

LR_RotaryGroup::~LR_RotaryGroup()
{
}

void LR_RotaryGroup::paint(juce::Graphics &g)
{
    //==============================================================================
    // draw an outline around the component
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

void LR_RotaryGroup::resized()
{
    typedef juce::FlexItem FlexItem;
    typedef juce::FlexBox FlexBox;

    const int sliderHeight = MIN_ROTARY_HEIGHT + MIN_TEXTBOX_HEIGHT;

    //==============================================================================
    // Main FlexBox
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.justifyContent = FlexBox::JustifyContent::spaceBetween;
    fb.alignItems = FlexBox::AlignItems::center;
    fb.flexWrap = FlexBox::Wrap::noWrap;

    //=============================================================================
    // FlexBoxes for rotary with label

    // Dry / wet
    FlexBox dryWet_L_FB;
    FlexBox dryWet_R_FB;

    dryWet_L_FB.flexDirection = FlexBox::Direction::column;
    dryWet_R_FB.flexDirection = FlexBox::Direction::column;

    dryWet_L_FB.justifyContent = FlexBox::JustifyContent::center;
    dryWet_R_FB.justifyContent = FlexBox::JustifyContent::center;

    dryWet_L_FB.alignItems = FlexBox::AlignItems::center;
    dryWet_R_FB.alignItems = FlexBox::AlignItems::center;

    dryWet_L_FB.flexWrap = FlexBox::Wrap::noWrap;
    dryWet_R_FB.flexWrap = FlexBox::Wrap::noWrap;

    dryWet_L_FB.items.add(FlexItem(dryWet_L_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    dryWet_L_FB.items.add(FlexItem(dryWet_L_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    dryWet_R_FB.items.add(FlexItem(dryWet_R_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    dryWet_R_FB.items.add(FlexItem(dryWet_R_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    // Feedback
    FlexBox feedback_L_FB;
    FlexBox feedback_R_FB;

    feedback_L_FB.flexDirection = FlexBox::Direction::column;
    feedback_R_FB.flexDirection = FlexBox::Direction::column;

    feedback_L_FB.justifyContent = FlexBox::JustifyContent::center;
    feedback_R_FB.justifyContent = FlexBox::JustifyContent::center;

    feedback_L_FB.alignItems = FlexBox::AlignItems::center;
    feedback_R_FB.alignItems = FlexBox::AlignItems::center;

    feedback_L_FB.flexWrap = FlexBox::Wrap::noWrap;
    feedback_R_FB.flexWrap = FlexBox::Wrap::noWrap;

    feedback_L_FB.items.add(FlexItem(feedback_L_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    feedback_L_FB.items.add(FlexItem(feedback_L_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));
                                            
    feedback_R_FB.items.add(FlexItem(feedback_R_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    feedback_R_FB.items.add(FlexItem(feedback_R_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    // Delay time
    FlexBox delayTime_L_FB;
    FlexBox delayTime_R_FB;

    delayTime_L_FB.flexDirection = FlexBox::Direction::column;
    delayTime_R_FB.flexDirection = FlexBox::Direction::column;

    delayTime_L_FB.justifyContent = FlexBox::JustifyContent::center;
    delayTime_R_FB.justifyContent = FlexBox::JustifyContent::center;

    delayTime_L_FB.alignItems = FlexBox::AlignItems::center;
    delayTime_R_FB.alignItems = FlexBox::AlignItems::center;

    delayTime_L_FB.flexWrap = FlexBox::Wrap::noWrap;
    delayTime_R_FB.flexWrap = FlexBox::Wrap::noWrap;

    delayTime_L_FB.items.add(FlexItem(delayTime_L_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    delayTime_L_FB.items.add(FlexItem(delayTime_L_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));
                                            
    delayTime_R_FB.items.add(FlexItem(delayTime_R_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    delayTime_R_FB.items.add(FlexItem(delayTime_R_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    // Low-pass cutoff
    FlexBox cutoffLP_L_FB;
    FlexBox cutoffLP_R_FB;

    cutoffLP_L_FB.flexDirection = FlexBox::Direction::column;
    cutoffLP_R_FB.flexDirection = FlexBox::Direction::column;

    cutoffLP_L_FB.justifyContent = FlexBox::JustifyContent::center;
    cutoffLP_R_FB.justifyContent = FlexBox::JustifyContent::center;

    cutoffLP_L_FB.alignItems = FlexBox::AlignItems::center;
    cutoffLP_R_FB.alignItems = FlexBox::AlignItems::center;

    cutoffLP_L_FB.flexWrap = FlexBox::Wrap::noWrap;
    cutoffLP_R_FB.flexWrap = FlexBox::Wrap::noWrap;

    cutoffLP_L_FB.items.add(FlexItem(cutoffLP_L_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    cutoffLP_L_FB.items.add(FlexItem(cutoffLP_L_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));
                                            
    cutoffLP_R_FB.items.add(FlexItem(cutoffLP_R_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    cutoffLP_R_FB.items.add(FlexItem(cutoffLP_R_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    // High-pass cutoff
    FlexBox cutoffHP_L_FB;
    FlexBox cutoffHP_R_FB;

    cutoffHP_L_FB.flexDirection = FlexBox::Direction::column;
    cutoffHP_R_FB.flexDirection = FlexBox::Direction::column;

    cutoffHP_L_FB.justifyContent = FlexBox::JustifyContent::center;
    cutoffHP_R_FB.justifyContent = FlexBox::JustifyContent::center;

    cutoffHP_L_FB.alignItems = FlexBox::AlignItems::center;
    cutoffHP_R_FB.alignItems = FlexBox::AlignItems::center;

    cutoffHP_L_FB.flexWrap = FlexBox::Wrap::noWrap;
    cutoffHP_R_FB.flexWrap = FlexBox::Wrap::noWrap;

    cutoffHP_L_FB.items.add(FlexItem(cutoffHP_L_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    cutoffHP_L_FB.items.add(FlexItem(cutoffHP_L_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));
                                            
    cutoffHP_R_FB.items.add(FlexItem(cutoffHP_R_Label).withMinHeight(MIN_LABEL_HEIGHT).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(MIN_LABEL_HEIGHT).withMaxWidth(MIN_ROTARY_WIDTH));
    cutoffHP_R_FB.items.add(FlexItem(cutoffHP_R_Slider).withMinHeight(sliderHeight).withMinWidth(MIN_ROTARY_WIDTH).withMaxHeight(sliderHeight).withMaxWidth(MIN_ROTARY_WIDTH));

    //==============================================================================
    // Flexboxes for the individual LR rotary pairs
    const int minPairWidth = 2 * MIN_ROTARY_WIDTH;

    // Dry / wet pair
    FlexBox dryWetFB;
    dryWetFB.flexDirection = FlexBox::Direction::row;
    dryWetFB.justifyContent = FlexBox::JustifyContent::spaceBetween;
    dryWetFB.alignItems = FlexBox::AlignItems::center;
    dryWetFB.flexWrap = FlexBox::Wrap::noWrap;

    dryWetFB.items.add(dryWet_L_FB);
    dryWetFB.items.add(dryWet_R_FB);

    // Feedback pair
    FlexBox feedbackFB;
    feedbackFB.flexDirection = FlexBox::Direction::row;
    feedbackFB.justifyContent = FlexBox::JustifyContent::spaceBetween;
    feedbackFB.alignItems = FlexBox::AlignItems::center;
    feedbackFB.flexWrap = FlexBox::Wrap::noWrap;

    feedbackFB.items.add(feedback_L_FB);
    feedbackFB.items.add(feedback_R_FB);
    
    // Delay time pair
    FlexBox delayTimeFB;
    delayTimeFB.flexDirection = FlexBox::Direction::row;
    delayTimeFB.justifyContent = FlexBox::JustifyContent::spaceBetween;
    delayTimeFB.alignItems = FlexBox::AlignItems::center;
    delayTimeFB.flexWrap = FlexBox::Wrap::noWrap;

    delayTimeFB.items.add(delayTime_L_FB);
    delayTimeFB.items.add(delayTime_R_FB);
    
    // Cutoff low-pass pair
    FlexBox cutoffLP_FB;
    cutoffLP_FB.flexDirection = FlexBox::Direction::row;
    cutoffLP_FB.justifyContent = FlexBox::JustifyContent::spaceBetween;
    cutoffLP_FB.alignItems = FlexBox::AlignItems::center;
    cutoffLP_FB.flexWrap = FlexBox::Wrap::noWrap;

    cutoffLP_FB.items.add(cutoffLP_L_FB);
    cutoffLP_FB.items.add(cutoffLP_R_FB);
    
    // Cutoff high-pass pair
    FlexBox cutoffHP_FB;
    cutoffHP_FB.flexDirection = FlexBox::Direction::row;
    cutoffHP_FB.justifyContent = FlexBox::JustifyContent::spaceBetween;
    cutoffHP_FB.alignItems = FlexBox::AlignItems::center;
    cutoffHP_FB.flexWrap = FlexBox::Wrap::noWrap;

    cutoffHP_FB.items.add(cutoffHP_L_FB);
    cutoffHP_FB.items.add(cutoffHP_R_FB);
    
    //==============================================================================
    // Make layout

    fb.items.add(FlexItem(dryWetFB).withMinWidth(minPairWidth).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(feedbackFB).withMinWidth(minPairWidth).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(delayTimeFB).withMinWidth(minPairWidth).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(cutoffLP_FB).withMinWidth(minPairWidth).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));
    fb.items.add(FlexItem(cutoffHP_FB).withMinWidth(minPairWidth).withMinHeight(sliderHeight + MIN_LABEL_HEIGHT));

    fb.performLayout(getLocalBounds().toFloat());
}
