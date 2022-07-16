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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    inputVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    outputVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

    inputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    inputVolumeAttachment.reset(new SliderAttachment(apvts, "inputVolume", inputVolumeSlider));
    outputVolumeAttachment.reset(new SliderAttachment(apvts, "outputVolume", outputVolumeSlider));

    addAndMakeVisible(&inputVolumeSlider);
    addAndMakeVisible(&outputVolumeSlider);
}

LR_DelayAudioProcessorEditor::~LR_DelayAudioProcessorEditor()
{
}

//==============================================================================
void LR_DelayAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void LR_DelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    inputVolumeSlider.setBounds(0, 0, getWidth() / 2, getHeight());
    outputVolumeSlider.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}
