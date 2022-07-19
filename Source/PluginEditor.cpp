/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessorEditor::LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts)
    : AudioProcessorEditor(&p), audioProcessor(p), apvts(apvts)
{
    setSize(width, height);
    setLookAndFeel(&customLook);

    //==============================================================================
    // Header / footer setup
    titleLabel.setFont(25.0f);
    titleLabel.setText("LR_DELAY", juce::NotificationType::dontSendNotification);
    titleLabel.setLookAndFeel(&customLook);

    versionLabel.setText("VERSION 0.1.0", juce::NotificationType::dontSendNotification);
    versionLabel.setLookAndFeel(&customLook);

    coprLabel.setText("B.W.", juce::NotificationType::dontSendNotification);
    coprLabel.setLookAndFeel(&customLook);

    websiteLabel.setText("HTTPS://BUTCHWARNS.DE/", juce::NotificationType::dontSendNotification);
    websiteLabel.setLookAndFeel(&customLook);

    //==============================================================================
    // Make all sliders rotary knobs
    typedef juce::Slider::SliderStyle SliderStyle;

    driveSlider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    driveSlider.setLookAndFeel(&customLook);

    volumeSlider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    volumeSlider.setLookAndFeel(&customLook);

    dryWet_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    dryWet_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    dryWet_L_Slider.setLookAndFeel(&customLook);
    dryWet_R_Slider.setLookAndFeel(&customLook);

    feedback_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    feedback_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    feedback_L_Slider.setLookAndFeel(&customLook);
    feedback_R_Slider.setLookAndFeel(&customLook);

    delayTime_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    delayTime_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    delayTime_L_Slider.setLookAndFeel(&customLook);
    delayTime_R_Slider.setLookAndFeel(&customLook);

    cutoffLP_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffLP_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffLP_L_Slider.setLookAndFeel(&customLook);
    cutoffLP_R_Slider.setLookAndFeel(&customLook);

    cutoffHP_L_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffHP_R_Slider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    cutoffHP_L_Slider.setLookAndFeel(&customLook);
    cutoffHP_R_Slider.setLookAndFeel(&customLook);

    stereoWidthSlider.setSliderStyle(SliderStyle::RotaryVerticalDrag);
    stereoWidthSlider.setLookAndFeel(&customLook);

    //==============================================================================
    // Make text boxes
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    driveSlider.setTextValueSuffix(" dB");

    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    volumeSlider.setTextValueSuffix(" dB");

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

    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, rotaryWidth, textBoxHeight);
    stereoWidthSlider.setTextValueSuffix(" %");

    //==============================================================================
    // Label the sliders
    driveLabel.setText("DRIVE", juce::NotificationType::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);

    volumeLabel.setText("VOLUME", juce::NotificationType::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred);

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

    stereoWidthLabel.setText("WIDTH", juce::NotificationType::dontSendNotification);
    stereoWidthLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================
    // Attach parameters in processor to sliders
    driveAttachment.reset(new SliderAttachment(apvts, "drive", driveSlider));
    volumeAttachment.reset(new SliderAttachment(apvts, "volume", volumeSlider));

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

    stereoWidthAttachment.reset(new SliderAttachment(apvts, "stereoWidth", stereoWidthSlider));

    //==============================================================================
    // Show all components
    addAndMakeVisible(&titleLabel);
    addAndMakeVisible(&versionLabel);
    addAndMakeVisible(&coprLabel);
    addAndMakeVisible(&websiteLabel);

    addAndMakeVisible(&driveSlider);
    addAndMakeVisible(&driveLabel);

    addAndMakeVisible(&volumeSlider);
    addAndMakeVisible(&volumeLabel);

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

    addAndMakeVisible(&stereoWidthSlider);
    addAndMakeVisible(&stereoWidthLabel);
}

LR_DelayAudioProcessorEditor::~LR_DelayAudioProcessorEditor()
{
    //==============================================================================
    titleLabel.setLookAndFeel(nullptr);
    versionLabel.setLookAndFeel(nullptr);
    coprLabel.setLookAndFeel(nullptr);
    websiteLabel.setLookAndFeel(nullptr);

    //==============================================================================
    driveSlider.setLookAndFeel(nullptr);
    volumeSlider.setLookAndFeel(nullptr);
    dryWet_L_Slider.setLookAndFeel(nullptr);
    dryWet_R_Slider.setLookAndFeel(nullptr);
    feedback_L_Slider.setLookAndFeel(nullptr);
    feedback_R_Slider.setLookAndFeel(nullptr);
    delayTime_L_Slider.setLookAndFeel(nullptr);
    delayTime_R_Slider.setLookAndFeel(nullptr);
    cutoffLP_L_Slider.setLookAndFeel(nullptr);
    cutoffLP_R_Slider.setLookAndFeel(nullptr);
    cutoffHP_L_Slider.setLookAndFeel(nullptr);
    cutoffHP_R_Slider.setLookAndFeel(nullptr);
    stereoWidthSlider.setLookAndFeel(nullptr);

    setLookAndFeel(nullptr);
}

//==============================================================================
void LR_DelayAudioProcessorEditor::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void LR_DelayAudioProcessorEditor::resized()
{
    //==============================================================================
    // Header / footer
    titleLabel.setBounds(0, 0, 100, 25);
    titleLabel.setJustificationType(juce::Justification::left);

    const int versionLabelWidth = 100;
    versionLabel.setBounds(width - versionLabelWidth, 0, versionLabelWidth, 25);
    versionLabel.setJustificationType(juce::Justification::right);

    coprLabel.setBounds(0, height - 25, 100, 25);
    coprLabel.setJustificationType(juce::Justification::left);

    const int websiteLabelWidth = 200;
    websiteLabel.setBounds(width - websiteLabelWidth, height - 25, websiteLabelWidth, 25);
    websiteLabel.setJustificationType(juce::Justification::right);

    //==============================================================================
    // Slider and their labels
    driveLabel.setBounds(0 * rotaryWidth, headerHeight + 0 * (rotaryHeight + labelHeight), rotaryWidth, labelHeight);
    driveSlider.setBounds(0 * rotaryWidth, headerHeight + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);

    volumeLabel.setBounds(0 * rotaryWidth, headerHeight + 1 * (rotaryHeight + labelHeight), rotaryWidth, labelHeight);
    volumeSlider.setBounds(0 * rotaryWidth, headerHeight + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);

    dryWet_L_Label.setBounds(1 * rotaryWidth, headerHeight + 0 * roLaHeight, rotaryWidth, labelHeight);
    dryWet_R_Label.setBounds(2 * rotaryWidth, headerHeight + 0 * roLaHeight, rotaryWidth, labelHeight);

    dryWet_L_Slider.setBounds(1 * rotaryWidth, headerHeight + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);
    dryWet_R_Slider.setBounds(2 * rotaryWidth, headerHeight + labelHeight + 0 * roLaHeight, rotaryWidth, rotaryHeight);

    feedback_L_Label.setBounds(1 * rotaryWidth, headerHeight + 1 * roLaHeight, rotaryWidth, labelHeight);
    feedback_R_Label.setBounds(2 * rotaryWidth, headerHeight + 1 * roLaHeight, rotaryWidth, labelHeight);

    feedback_L_Slider.setBounds(1 * rotaryWidth, headerHeight + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);
    feedback_R_Slider.setBounds(2 * rotaryWidth, headerHeight + labelHeight + 1 * roLaHeight, rotaryWidth, rotaryHeight);

    delayTime_L_Label.setBounds(1 * rotaryWidth, headerHeight + 2 * roLaHeight, rotaryWidth, labelHeight);
    delayTime_R_Label.setBounds(2 * rotaryWidth, headerHeight + 2 * roLaHeight, rotaryWidth, labelHeight);

    delayTime_L_Slider.setBounds(1 * rotaryWidth, headerHeight + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);
    delayTime_R_Slider.setBounds(2 * rotaryWidth, headerHeight + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);

    cutoffLP_L_Label.setBounds(1 * rotaryWidth, headerHeight + 3 * roLaHeight, rotaryWidth, labelHeight);
    cutoffLP_R_Label.setBounds(2 * rotaryWidth, headerHeight + 3 * roLaHeight, rotaryWidth, labelHeight);

    cutoffLP_L_Slider.setBounds(1 * rotaryWidth, headerHeight + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);
    cutoffLP_R_Slider.setBounds(2 * rotaryWidth, headerHeight + labelHeight + 3 * roLaHeight, rotaryWidth, rotaryHeight);

    cutoffHP_L_Label.setBounds(1 * rotaryWidth, headerHeight + 4 * roLaHeight, rotaryWidth, labelHeight);
    cutoffHP_R_Label.setBounds(2 * rotaryWidth, headerHeight + 4 * roLaHeight, rotaryWidth, labelHeight);

    cutoffHP_L_Slider.setBounds(1 * rotaryWidth, headerHeight + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);
    cutoffHP_R_Slider.setBounds(2 * rotaryWidth, headerHeight + labelHeight + 4 * roLaHeight, rotaryWidth, rotaryHeight);

    stereoWidthLabel.setBounds(0 * rotaryWidth, headerHeight + 2 * roLaHeight, rotaryWidth, labelHeight);
    stereoWidthSlider.setBounds(0 * rotaryWidth, headerHeight + labelHeight + 2 * roLaHeight, rotaryWidth, rotaryHeight);
}
