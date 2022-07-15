/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "delay.h"

//==============================================================================
// Declarations needed for faust dsp integration to work
class dsp;
class MapUI;

//==============================================================================
/**
 */
class LR_DelayAudioProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
#if JucePlugin_Enable_ARA
    ,
                               public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    LR_DelayAudioProcessor();
    ~LR_DelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    //==============================================================================
    // juce::AudiopProcessorValueTree::Listener interface
    void parameterChanged(const juce::String &parameterId, float newValue) override;

private:
    juce::AudioProcessorValueTreeState parameters;
    juce::UndoManager undoManager;
    
    //==============================================================================
    // Parameters

    std::atomic<float> *inputVolume;
    std::atomic<float> *outputVolume;

    std::atomic<float> *dryWet_L;
    std::atomic<float> *dryWet_R;

    std::atomic<float> *feedback_L;
    std::atomic<float> *feedback_R;

    std::atomic<float> *delayTime_L;
    std::atomic<float> *delayTime_R;

    std::atomic<float> *cutoffLP_L;
    std::atomic<float> *cutoffLP_R;

    std::atomic<float> *cutoffHP_L;
    std::atomic<float> *cutoffHP_R;

    std::atomic<float> *stereoWidth;

    //==============================================================================
    // Faust dsp objects

    std::unique_ptr<::Delay> fDELAY; // Delay dsp class
    std::unique_ptr<::MapUI> fUI; // Parameter handling

    float **faustIO; // Input/output arrays

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_DelayAudioProcessor)
};
