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
    addAndMakeVisible(&dryWet_L_Slider);
    addAndMakeVisible(&dryWet_R_Slider);
    addAndMakeVisible(&dryWetLabel);

    addAndMakeVisible(&feedback_L_Slider);
    addAndMakeVisible(&feedback_R_Slider);
    addAndMakeVisible(&feedbackLabel);

    addAndMakeVisible(&delayTime_L_Slider);
    addAndMakeVisible(&delayTime_R_Slider);
    addAndMakeVisible(&delayTimeLabel);

    addAndMakeVisible(&cutoffLP_L_Slider);
    addAndMakeVisible(&cutoffLP_R_Slider);
    addAndMakeVisible(&cutoffLP_Label);

    addAndMakeVisible(&cutoffHP_L_Slider);
    addAndMakeVisible(&cutoffHP_R_Slider);
    addAndMakeVisible(&cutoffHP_Label);

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
    dryWet_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    dryWet_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    dryWet_L_Slider.setTextValueSuffix(" %");
    dryWet_R_Slider.setTextValueSuffix(" %");

    feedback_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    feedback_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    feedback_L_Slider.setTextValueSuffix(" %");
    feedback_R_Slider.setTextValueSuffix(" %");

    delayTime_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    delayTime_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    delayTime_L_Slider.setTextValueSuffix(" ms");
    delayTime_R_Slider.setTextValueSuffix(" ms");

    cutoffLP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffLP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffLP_L_Slider.setTextValueSuffix(" Hz");
    cutoffLP_R_Slider.setTextValueSuffix(" Hz");

    cutoffHP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffHP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, MIN_ROTARY_WIDTH, MIN_SLIDER_TEXTBOX_HEIGHT);
    cutoffHP_L_Slider.setTextValueSuffix(" Hz");
    cutoffHP_R_Slider.setTextValueSuffix(" Hz");

    //==============================================================================
    // Label the sliders
    dryWetLabel.setText("DRY / WET", juce::NotificationType::dontSendNotification);
    dryWetLabel.setJustificationType(juce::Justification::centred);

    feedbackLabel.setText("FEEDBACK", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);

    delayTimeLabel.setText("DELAY TIME", juce::NotificationType::dontSendNotification);
    delayTimeLabel.setJustificationType(juce::Justification::centred);

    cutoffLP_Label.setText("LP CUTOFF", juce::NotificationType::dontSendNotification);
    cutoffLP_Label.setJustificationType(juce::Justification::centred);

    cutoffHP_Label.setText("HP CUTOFF", juce::NotificationType::dontSendNotification);
    cutoffHP_Label.setJustificationType(juce::Justification::centred);

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

LR_RotaryGroup::~LR_RotaryGroup() {}

void LR_RotaryGroup::paint(juce::Graphics &g) {}

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

    // FlexBoxes for rotary pairs with label
    FlexBox dryWetFB;
    FlexBox feedbackFB;
    FlexBox delayTimeFB;
    FlexBox cutoffLP_FB;
    FlexBox cutoffHP_FB;

    setupSliderPairAndLabel(dryWetFB);
    setupSliderPairAndLabel(feedbackFB);
    setupSliderPairAndLabel(delayTimeFB);
    setupSliderPairAndLabel(cutoffLP_FB);
    setupSliderPairAndLabel(cutoffHP_FB);

    // Pairs of rotary sliders for L / R
    FlexBox dryWetPair;
    FlexBox feedbackPair;
    FlexBox delayTimePair;
    FlexBox cutoffLP_Pair;
    FlexBox cutoffHP_Pair;

    setupSliderPair(dryWetPair);
    setupSliderPair(feedbackPair);
    setupSliderPair(delayTimePair);
    setupSliderPair(cutoffLP_Pair);
    setupSliderPair(cutoffHP_Pair);

    // Individual sliders and labels as FlexItems
    FlexItem flexDryWet_L_Slider = makeFlexSlider(dryWet_L_Slider);
    FlexItem flexDryWet_R_Slider = makeFlexSlider(dryWet_R_Slider);

    FlexItem flexFeedback_L_Slider = makeFlexSlider(feedback_L_Slider);
    FlexItem flexFeedback_R_Slider = makeFlexSlider(feedback_R_Slider);

    FlexItem flexDelayTime_L_Slider = makeFlexSlider(delayTime_L_Slider);
    FlexItem flexDelayTime_R_Slider = makeFlexSlider(delayTime_R_Slider);

    FlexItem flexCutoffLP_L_Slider = makeFlexSlider(cutoffLP_L_Slider);
    FlexItem flexCutoffLP_R_Slider = makeFlexSlider(cutoffLP_R_Slider);

    FlexItem flexCutoffHP_L_Slider = makeFlexSlider(cutoffHP_L_Slider);
    FlexItem flexCutoffHP_R_Slider = makeFlexSlider(cutoffHP_R_Slider);

    // Add sliders to the pair boxes
    dryWetPair.items.add(flexDryWet_L_Slider);
    dryWetPair.items.add(flexDryWet_R_Slider);

    feedbackPair.items.add(flexFeedback_L_Slider);
    feedbackPair.items.add(flexFeedback_R_Slider);

    delayTimePair.items.add(flexDelayTime_L_Slider);
    delayTimePair.items.add(flexDelayTime_R_Slider);

    cutoffLP_Pair.items.add(flexCutoffLP_L_Slider);
    cutoffLP_Pair.items.add(flexCutoffLP_R_Slider);

    cutoffHP_Pair.items.add(flexCutoffHP_L_Slider);
    cutoffHP_Pair.items.add(flexCutoffHP_R_Slider);

    // Labels for the rotary pairs as FlexItems
    FlexItem flexDryWetLabel = makeFlexLabel(dryWetLabel);
    FlexItem flexFeedbackLabel = makeFlexLabel(feedbackLabel);
    FlexItem flexDelayTimeLabel = makeFlexLabel(delayTimeLabel);
    FlexItem flexCutoffLP_Label = makeFlexLabel(cutoffLP_Label);
    FlexItem flexCutoffHP_Label = makeFlexLabel(cutoffHP_Label);

    // Pairs of rotary encoders as FlexItems
    FlexItem flexDryWetPair = makeFlexPair(dryWetPair);
    FlexItem flexFeedbackPair = makeFlexPair(feedbackPair);
    FlexItem flexDelayTimePair = makeFlexPair(delayTimePair);
    FlexItem flexCutoffLP_Pair = makeFlexPair(cutoffLP_Pair);
    FlexItem flexCutoffHP_Pair = makeFlexPair(cutoffHP_Pair);

    // Add pairs and labels to their FlexBoxes
    dryWetFB.items.add(flexDryWetLabel);
    dryWetFB.items.add(flexDryWetPair);

    feedbackFB.items.add(flexFeedbackLabel);
    feedbackFB.items.add(flexFeedbackPair);

    delayTimeFB.items.add(flexDelayTimeLabel);
    delayTimeFB.items.add(flexDelayTimePair);

    cutoffLP_FB.items.add(flexCutoffLP_Label);
    cutoffLP_FB.items.add(flexCutoffLP_Pair);

    cutoffHP_FB.items.add(flexCutoffHP_Label);
    cutoffHP_FB.items.add(flexCutoffHP_Pair);

    // Pairs and labels as FlexItems
    FlexItem flexDryWetFB = makeFlexPairAndLabel(dryWetFB);
    FlexItem flexFeedbackFB = makeFlexPairAndLabel(feedbackFB);
    FlexItem flexDelayTimeFB = makeFlexPairAndLabel(delayTimeFB);
    FlexItem flexCutoffLP_FB = makeFlexPairAndLabel(cutoffLP_FB);
    FlexItem flexCutoffHP_FB = makeFlexPairAndLabel(cutoffHP_FB);

    //==============================================================================
    // Add rotary pairs with labels to layout
    fb.items.add(flexDryWetFB);
    fb.items.add(flexFeedbackFB);
    fb.items.add(flexDelayTimeFB);
    fb.items.add(flexCutoffLP_FB);
    fb.items.add(flexCutoffHP_FB);

    //==============================================================================
    fb.performLayout(getLocalBounds());
}

//==============================================================================
// FlexBox helpers

void LR_RotaryGroup::setupSliderAndLabel(juce::FlexBox &fb)
{
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
}

void LR_RotaryGroup::setupSliderPair(juce::FlexBox &fb)
{
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
}

void LR_RotaryGroup::setupSliderPairAndLabel(juce::FlexBox &fb)
{
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
}

juce::FlexItem LR_RotaryGroup::makeFlexSlider(juce::Slider &s)
{
    juce::FlexItem flexItem(s);

    flexItem = flexItem.withMinWidth(MIN_ROTARY_WIDTH)
                   .withMinHeight(MIN_SLIDER_HEIGHT)
                   .withFlex(1.0f);

    return flexItem;
}

juce::FlexItem LR_RotaryGroup::makeFlexLabel(juce::Label &l)
{
    juce::FlexItem flexItem(l);

    flexItem = flexItem.withMinWidth(MIN_ROTARY_WIDTH)
                   .withMinHeight(MIN_SLIDER_LABEL_HEIGHT)
                   .withFlex(1.0f);

    return flexItem;
}

juce::FlexItem LR_RotaryGroup::makeFlexPair(juce::FlexBox &pair)
{
    juce::FlexItem flexItem(pair);

    flexItem = flexItem.withMinWidth(2 * MIN_ROTARY_WIDTH)
                   .withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT)
                   .withFlex(1.0f);

    return flexItem;
}

juce::FlexItem LR_RotaryGroup::makeFlexPairAndLabel(juce::FlexBox &pairAndLabel)
{
    juce::FlexItem flexItem(pairAndLabel);

    flexItem = flexItem.withMinWidth(2 * MIN_ROTARY_WIDTH)
                   .withMinHeight(MIN_SLIDER_WITH_LABEL_HEIGHT)
                   .withFlex(1.0f);

    return flexItem;
}