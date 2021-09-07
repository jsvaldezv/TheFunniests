#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyEQAudioProcessor::FunnyEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, PARAMETERS, initializeGUI())
#endif
{
    initializeDSP();
}

FunnyEQAudioProcessor::~FunnyEQAudioProcessor(){}

void FunnyEQAudioProcessor::initializeDSP()
{
    for(int i = 0; i < getTotalNumOutputChannels(); i++)
    {
        ptrLowPass[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::LPF));
        ptrHighPass[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::HPF));
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout FunnyEQAudioProcessor::initializeGUI()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //HIGH PASSS FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(HIGH_FREQ_ID,
                                                                 HIGH_FREQ_NAME,
                                                                 50.0f,
                                                                 18000.0f,
                                                                 100.0f));
    //HIGH PASSS GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(HIGH_GAIN_ID,
                                                                 HIGH_GAIN_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0f));
    //LOW PASSS FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(LOW_FREQ_ID,
                                                                 LOW_FREQ_NAME,
                                                                 50.0f,
                                                                 10000.0f,
                                                                 5000.0f));
    //LOW PASSS GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(LOW_GAIN_ID,
                                                                 LOW_GAIN_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0f));
    
    return {params.begin(), params.end()};
}

const juce::String FunnyEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FunnyEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FunnyEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FunnyEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FunnyEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FunnyEQAudioProcessor::getNumPrograms()
{
    return 1;
}

int FunnyEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FunnyEQAudioProcessor::setCurrentProgram (int index){}

const juce::String FunnyEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void FunnyEQAudioProcessor::changeProgramName (int index, const juce::String& newName){}

void FunnyEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for(int i = 0; i < getTotalNumOutputChannels(); i++)
    {
        ptrLowPass[i]->prepare(sampleRate);
        ptrHighPass[i]->prepare(sampleRate);
    }
}

void FunnyEQAudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FunnyEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FunnyEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        ptrLowPass[channel]->process(channelData,
                                     channelData,
                                     buffer.getNumSamples(),
                                     *parameters.getRawParameterValue(LOW_FREQ_ID),
                                     *parameters.getRawParameterValue(LOW_GAIN_ID),
                                     EQ_Filters::FilterType::LPF);
        
        ptrHighPass[channel]->process(channelData,
                                      channelData,
                                      buffer.getNumSamples(),
                                      *parameters.getRawParameterValue(HIGH_FREQ_ID),
                                      *parameters.getRawParameterValue(HIGH_GAIN_ID),
                                      EQ_Filters::FilterType::HPF);
    }
}

bool FunnyEQAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FunnyEQAudioProcessor::createEditor()
{
    return new FunnyEQAudioProcessorEditor (*this);
}

void FunnyEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}

void FunnyEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FunnyEQAudioProcessor();
}
