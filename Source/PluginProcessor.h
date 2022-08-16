/*
  ==============================================================================

    PluginProcessor.h

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
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    void parameterChanged(const juce::String &parameterId, float newValue) override;

    //==============================================================================
    juce::AudioProcessorValueTreeState &getApvts();

private:
    juce::AudioProcessorValueTreeState parameters;
    juce::UndoManager undoManager;

    //==============================================================================
    // Parameters
    std::atomic<float> *drive;
    std::atomic<float> *volume;

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
    std::unique_ptr<::MapUI> fUI;    // Parameter handling

    //==============================================================================
    // Oversampling to run Faust dsp at higher samplerate
    std::unique_ptr<juce::dsp::Oversampling<float>> oversampling;
    const int OVERSAMPLING_FACTOR = 4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LR_DelayAudioProcessor)
};
