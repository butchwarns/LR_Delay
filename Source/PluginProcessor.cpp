/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LR_DelayAudioProcessor::LR_DelayAudioProcessor() : parameters(*this, &undoManager, "parameters",
                                                              {
                                                                  std::make_unique<juce::AudioParameterFloat>("inputVolume", "IN_VOLUME", -24.0f, 12.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("outputVolume", "OUT_VOLUME", -24.0f, 12.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("dryWet_L", "DRY_WET_L", 0.0f, 100.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("dryWet_R", "DRY_WET_R", 0.0f, 100.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("feedback_L", "FEEDBACK_L", 0.0f, 100.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("feedback_R", "FEEDBACK_R", 0.0f, 100.0f, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("delayTime_L", "DELAY_TIME_L", 0.0f, 1500.0, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("delayTime_R", "DELAY_TIME_L", 0.0f, 1500.0, 0.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("cutoffLP_L", "CUTOFF_LP_L", 20.0f, 20000.0f, 20000.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("cutoffLP_R", "CUTOFF_LP_R", 20.0f, 20000.0f, 20000.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("cutoffHP_L", "CUTOFF_HP_L", 20.0f, 20000.0f, 20.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("cutoffHP_R", "CUTOFF_HP_R", 20.0f, 20000.0f, 20.0f),
                                                                  std::make_unique<juce::AudioParameterFloat>("stereoWidth", "STEREO_WIDTH", 0.0f, 100.0f, 100.0f),
                                                              })
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
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

    inputVolume = parameters.getRawParameterValue("inputVolume");
    outputVolume = parameters.getRawParameterValue("outputVolume");
    parameters.addParameterListener("inputVolume", this);
    parameters.addParameterListener("outputVolume", this);

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
    // Listen to parameter changes

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
    fDELAY->init(sampleRate);
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
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
    }

    //==============================================================================
    // Faust DSP computation
    const int bufferSize = buffer.getNumSamples();
    faustIO = buffer.getArrayOfWritePointers();

    fDELAY->compute(bufferSize, faustIO, faustIO); // Process!
}

//==============================================================================
bool LR_DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *LR_DelayAudioProcessor::createEditor()
{
    // return new LR_DelayAudioProcessorEditor (*this);
    return new LR_DelayAudioProcessorEditor(*this, parameters);
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

    if(xmlState.get() != nullptr)
    {
        if(xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
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
// Hand over parameter changes to Faust DSP code
void LR_DelayAudioProcessor::parameterChanged(const juce::String &parameterId, float newValue)
{
    fUI->setParamValue(parameterId.toStdString(), newValue);
}