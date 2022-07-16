/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class LR_DelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    LR_DelayAudioProcessorEditor(LR_DelayAudioProcessor &p, juce::AudioProcessorValueTreeState &apvts);
    ~LR_DelayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LR_DelayAudioProcessor &audioProcessor;

    //==============================================================================
    // UI elements
    juce::Slider inputVolumeSlider;
    juce::Slider outputVolumeSlider;

    // Attachments to the parameters
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    std::unique_ptr<SliderAttachment> inputVolumeAttachment;
    std::unique_ptr<SliderAttachment> outputVolumeAttachment;

    // Reference to the AudioProcessorValueTreeState object in the Processor
    juce::AudioProcessorValueTreeState &apvts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_DelayAudioProcessorEditor)
};
