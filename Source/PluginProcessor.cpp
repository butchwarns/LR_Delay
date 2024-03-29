/*
  ==============================================================================

    PluginProcessor.cpp

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

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessor::LR_DelayAudioProcessor() : parameters(*this, &undoManager, "parameters", getParameterLayout()),
#ifndef JucePlugin_PreferredChannelConfigurations
                                                   AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                                                      .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                                                                      .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                                                   )
#endif
{
    //==============================================================================
    // Get pointers to all parameter values and listen to value changes

    drive = parameters.getRawParameterValue("drive");
    parameters.addParameterListener("drive", this);

    volume = parameters.getRawParameterValue("volume");
    parameters.addParameterListener("volume", this);

    dryWet_L = parameters.getRawParameterValue("dryWet_L");
    dryWet_R = parameters.getRawParameterValue("dryWet_R");
    parameters.addParameterListener("dryWet_L", this);
    parameters.addParameterListener("dryWet_R", this);

    feedback_L = parameters.getRawParameterValue("feedback_L");
    feedback_R = parameters.getRawParameterValue("feedback_R");
    parameters.addParameterListener("feedback_L", this);
    parameters.addParameterListener("feedback_R", this);

    delayTime_L = parameters.getRawParameterValue("delayTime_L");
    delayTime_R = parameters.getRawParameterValue("delayTime_R");
    parameters.addParameterListener("delayTime_L", this);
    parameters.addParameterListener("delayTime_R", this);

    preDelay_L = parameters.getRawParameterValue("preDelay_L");
    preDelay_R = parameters.getRawParameterValue("preDelay_R");
    parameters.addParameterListener("preDelay_L", this);
    parameters.addParameterListener("preDelay_R", this);

    cutoffLP_L = parameters.getRawParameterValue("cutoffLP_L");
    cutoffLP_R = parameters.getRawParameterValue("cutoffLP_R");
    parameters.addParameterListener("cutoffLP_L", this);
    parameters.addParameterListener("cutoffLP_R", this);

    cutoffHP_L = parameters.getRawParameterValue("cutoffHP_L");
    cutoffHP_R = parameters.getRawParameterValue("cutoffHP_R");
    parameters.addParameterListener("cutoffHP_L", this);
    parameters.addParameterListener("cutoffHP_R", this);

    stereoWidth = parameters.getRawParameterValue("stereoWidth");
    parameters.addParameterListener("stereoWidth", this);

    //==============================================================================
    // Oversampling
    typedef juce::dsp::Oversampling<float> Oversampling;
    oversampling.reset(new Oversampling(2, log2(OVERSAMPLING_FACTOR), Oversampling::FilterType::filterHalfBandPolyphaseIIR, true, true));

    //==============================================================================

    // Make faust objects
    fDELAY = std::make_unique<::Delay>();
    fUI = std::make_unique<::MapUI>();

    // Attach UI to DSP
    fDELAY->buildUserInterface(fUI.get());
}

LR_DelayAudioProcessor::~LR_DelayAudioProcessor()
{
}

//==============================================================================
const juce::String LR_DelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LR_DelayAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LR_DelayAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool LR_DelayAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double LR_DelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LR_DelayAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int LR_DelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LR_DelayAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String LR_DelayAudioProcessor::getProgramName(int index)
{
    return {};
}

void LR_DelayAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
}

//==============================================================================
void LR_DelayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Init oversampling
    oversampling->initProcessing(static_cast<size_t>(samplesPerBlock));
    oversampling->reset();

    // Init Faust dsp
    fDELAY->init(static_cast<int>(sampleRate * OVERSAMPLING_FACTOR));

    // "Touch" all parameters to propagate the restored state
    parameterChanged("drive", *drive);
    parameterChanged("volume", *volume);
    parameterChanged("dryWet_L", *dryWet_L);
    parameterChanged("dryWet_R", *dryWet_R);
    parameterChanged("feedback_L", *feedback_L);
    parameterChanged("feedback_R", *feedback_R);
    parameterChanged("delayTime_L", *delayTime_L);
    parameterChanged("delayTime_R", *delayTime_R);
    parameterChanged("preDelay_L", *preDelay_L);
    parameterChanged("preDelay_R", *preDelay_R);
    parameterChanged("cutoffLP_L", *cutoffLP_L);
    parameterChanged("cutoffLP_R", *cutoffLP_R);
    parameterChanged("cutoffHP_L", *cutoffHP_L);
    parameterChanged("cutoffHP_R", *cutoffHP_R);
    parameterChanged("stereoWidth", *stereoWidth);
}

void LR_DelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LR_DelayAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void LR_DelayAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     auto *channelData = buffer.getWritePointer(channel);

    //     // ..do something to the data...
    // }

    //==============================================================================
    // Upsampling for antialiasing reasons
    juce::dsp::AudioBlock<float> IOBlock(buffer);
    juce::dsp::AudioBlock<float> oversampledBlock = oversampling->processSamplesUp(IOBlock);

    buffer.clear();
    //==============================================================================
    // Faust DSP computation
    float *faustIO[2]{0};
    faustIO[0] = oversampledBlock.getChannelPointer(0);
    faustIO[1] = oversampledBlock.getChannelPointer(1);

    fDELAY->compute(buffer.getNumSamples() * OVERSAMPLING_FACTOR, faustIO, faustIO);

    // //==============================================================================
    // // Downsampling
    oversampling->processSamplesDown(IOBlock);
}

//==============================================================================
bool LR_DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *LR_DelayAudioProcessor::createEditor()
{
    // return new LR_DelayAudioProcessorEditor (*this);
    return new LR_DelayAudioProcessorEditor(*this);
}

//==============================================================================
void LR_DelayAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LR_DelayAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            juce::ValueTree state = juce::ValueTree::fromXml(*xmlState);
            parameters.replaceState(state);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new LR_DelayAudioProcessor();
}

//==============================================================================
// Parameters

juce::AudioProcessorValueTreeState::ParameterLayout LR_DelayAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout(
        {
            // Do not forget to add new parameters to setStateInformation() to enable restoring the state!
            std::make_unique<juce::AudioParameterFloat>("drive", "DRIVE", juce::NormalisableRange<float>(-12.0f, 16.0f, 0.1f, 1.0f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", juce::NormalisableRange<float>(-24.0f, 12.0f, 0.1f, 1.0f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("dryWet_L", "DRY_WET_L", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("dryWet_R", "DRY_WET_R", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("feedback_L", "FEEDBACK_L", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("feedback_R", "FEEDBACK_R", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("delayTime_L", "DELAY_TIME_L", juce::NormalisableRange<float>(0.0f, 1500.0f, 0.1f, 0.75f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("delayTime_R", "DELAY_TIME_L", juce::NormalisableRange<float>(0.0f, 1500.0f, 0.1f, 0.75f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("preDelay_L", "PRE_DELAY_L", juce::NormalisableRange<float>(0.0f, 1500.0f, 0.1f, 0.33f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("preDelay_R", "PRE_DELAY_R", juce::NormalisableRange<float>(0.0f, 1500.0f, 0.1f, 0.33f), 0.0f),
            std::make_unique<juce::AudioParameterFloat>("cutoffLP_L", "CUTOFF_LP_L", juce::NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.33f), 20000.0f),
            std::make_unique<juce::AudioParameterFloat>("cutoffLP_R", "CUTOFF_LP_R", juce::NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.33f), 20000.0f),
            std::make_unique<juce::AudioParameterFloat>("cutoffHP_L", "CUTOFF_HP_L", juce::NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.33f), 20.0f),
            std::make_unique<juce::AudioParameterFloat>("cutoffHP_R", "CUTOFF_HP_R", juce::NormalisableRange<float>(20.0f, 20000.0f, 0.1f, 0.33f), 20.0f),
            std::make_unique<juce::AudioParameterFloat>("stereoWidth", "STEREO_WIDTH", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 100.0f),
        });

    return layout;
}

// Hand over parameter changes to Faust DSP code
void LR_DelayAudioProcessor::parameterChanged(const juce::String &parameterId, float newValue)
{
    fUI->setParamValue(parameterId.toStdString(), newValue);
}

// Getter for the AudioProcessorValueTree handling all parameters to be passed to child components
juce::AudioProcessorValueTreeState &LR_DelayAudioProcessor::getApvts()
{
    return parameters;
}