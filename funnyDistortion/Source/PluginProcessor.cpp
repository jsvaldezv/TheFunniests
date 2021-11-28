#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyDistortionAudioProcessor::FunnyDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "PARAMETERS", initializeGUI())
#endif
{
    for(int i = 0; i < getTotalNumInputChannels(); i++)
    {
        ptrDistor[i] = std::make_unique<funnyDistortion>();
        ptrVolume[i] = std::make_unique<funnyVolumen>();
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout FunnyDistortionAudioProcessor::initializeGUI()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //VOLUMEN SLIDER
    params.push_back(std::make_unique<juce::AudioParameterFloat>(VOLUME_ID,
                                                                 VOLUME_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0));
    
    //DRIVE SLIDER
    params.push_back(std::make_unique<juce::AudioParameterFloat>(DRIVE_ID,
                                                                 DRIVE_NAME,
                                                                 0.0001f,
                                                                 1.0f,
                                                                 0.5f));
    
    //RANGE SLIDER
    params.push_back(std::make_unique<juce::AudioParameterFloat>(RANGE_ID,
                                                                 RANGE_NAME,
                                                                 0.0001f,
                                                                 3000.0f,
                                                                 300.0f));
    
    //BLEND SLIDER
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BLEND_ID,
                                                                 BLEND_NAME,
                                                                 0.1f,
                                                                 1.0f,
                                                                 0.6f));
    
    //TYPE COMBOBOX
    params.push_back(std::make_unique<juce::AudioParameterChoice>(TYPE_ID,
                                                                  TYPE_NAME,
                                                                  juce::StringArray("Something Broken",
                                                                                    "Television",
                                                                                    "Intercepted Transmission"),0));
    
    return {params.begin(),params.end()};
}

FunnyDistortionAudioProcessor::~FunnyDistortionAudioProcessor(){}

const juce::String FunnyDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FunnyDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FunnyDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FunnyDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FunnyDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FunnyDistortionAudioProcessor::getNumPrograms()
{
    return 1;
}

int FunnyDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FunnyDistortionAudioProcessor::setCurrentProgram (int index){}

const juce::String FunnyDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void FunnyDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName){}

void FunnyDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){}

void FunnyDistortionAudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FunnyDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FunnyDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        ptrDistor[channel]->process(channelData,
                                    channelData,
                                    numSamples,
                                    *parameters.getRawParameterValue(DRIVE_ID),
                                    *parameters.getRawParameterValue(RANGE_ID),
                                    *parameters.getRawParameterValue(BLEND_ID),
                                    *parameters.getRawParameterValue(TYPE_ID));
        
        ptrVolume[channel]->process(channelData,
                                    channelData,
                                    *parameters.getRawParameterValue(VOLUME_ID),
                                    numSamples);
    }
}

bool FunnyDistortionAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FunnyDistortionAudioProcessor::createEditor()
{
    return new FunnyDistortionAudioProcessorEditor (*this);
}

void FunnyDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}

void FunnyDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FunnyDistortionAudioProcessor();
}
