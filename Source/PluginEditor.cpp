/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessorEditor::LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts)
    : AudioProcessorEditor(&p), audioProcessor(p), apvts(apvts), utilityRotaryGroup(apvts)
{
    // Set main window size
    setSize(width, height);

    //==============================================================================
    // Add children
    addChildComponent(header);
    addChildComponent(footer);

    addChildComponent(utilityRotaryGroup);

    addChildComponent(dryWet_L_Slider);
    addChildComponent(dryWet_R_Slider);
    addChildComponent(feedback_L_Slider);
    addChildComponent(feedback_R_Slider);
    addChildComponent(delayTime_L_Slider);
    addChildComponent(delayTime_R_Slider);
    addChildComponent(cutoffLP_L_Slider);
    addChildComponent(cutoffLP_R_Slider);
    addChildComponent(cutoffHP_L_Slider);
    addChildComponent(cutoffHP_R_Slider);

    //==============================================================================
    // Set "global" look and feel
    setLookAndFeel(&customLook);

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
    dryWet_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    dryWet_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    dryWet_L_Slider.setTextValueSuffix(" %");
    dryWet_R_Slider.setTextValueSuffix(" %");

    feedback_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    feedback_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    feedback_L_Slider.setTextValueSuffix(" %");
    feedback_R_Slider.setTextValueSuffix(" %");

    delayTime_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    delayTime_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    delayTime_L_Slider.setTextValueSuffix(" ms");
    delayTime_R_Slider.setTextValueSuffix(" ms");

    cutoffLP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    cutoffLP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    cutoffLP_L_Slider.setTextValueSuffix(" Hz");
    cutoffLP_R_Slider.setTextValueSuffix(" Hz");

    cutoffHP_L_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    cutoffHP_R_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
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

    //==============================================================================
    // Show all components
    addAndMakeVisible(&header);
    addAndMakeVisible(&footer);

    addAndMakeVisible(&utilityRotaryGroup);

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
}

LR_DelayAudioProcessorEditor::~LR_DelayAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void LR_DelayAudioProcessorEditor::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void LR_DelayAudioProcessorEditor::resized()
{
    typedef juce::Rectangle<int> Rect;
    Rect localBounds = getLocalBounds();

    Rect headerArea = localBounds.removeFromTop(HEADER_HEIGHT);
    Rect footerArea = localBounds.removeFromBottom(FOOTER_HEIGHT);
    Rect utilArea = localBounds.removeFromLeft(100);

    //==============================================================================
    // Header & footer

    header.setBounds(headerArea);
    footer.setBounds(footerArea);

    utilityRotaryGroup.setBounds(utilArea);

    //==============================================================================
    // Slider and their labels
    // dryWet_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 0 * roLaHeight, rotaryWidth, labelHeight);
    // dryWet_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 0 * roLaHeight, rotaryWidth, labelHeight);

    // dryWet_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);
    // dryWet_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);

    // feedback_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 1 * roLaHeight, rotaryWidth, labelHeight);
    // feedback_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 1 * roLaHeight, rotaryWidth, labelHeight);

    // feedback_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);
    // feedback_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);

    // delayTime_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 2 * roLaHeight, rotaryWidth, labelHeight);
    // delayTime_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 2 * roLaHeight, rotaryWidth, labelHeight);

    // delayTime_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);
    // delayTime_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);

    // cutoffLP_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 3 * roLaHeight, rotaryWidth, labelHeight);
    // cutoffLP_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 3 * roLaHeight, rotaryWidth, labelHeight);

    // cutoffLP_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);
    // cutoffLP_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);

    // cutoffHP_L_Label.setBounds(1 * rotaryWidth, HEADER_HEIGHT + 4 * roLaHeight, rotaryWidth, labelHeight);
    // cutoffHP_R_Label.setBounds(2 * rotaryWidth, HEADER_HEIGHT + 4 * roLaHeight, rotaryWidth, labelHeight);

    // cutoffHP_L_Slider.setBounds(1 * rotaryWidth, HEADER_HEIGHT + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);
    // cutoffHP_R_Slider.setBounds(2 * rotaryWidth, HEADER_HEIGHT + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);
}
