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
        ptrBandOne[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::LPF));
        ptrBandTwo[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::HPF));
        ptrBandThree[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::LPF));
        ptrBandFour[i] = std::unique_ptr<EQ_Filters>(new EQ_Filters(EQ_Filters::FilterType::HPF));
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout FunnyEQAudioProcessor::initializeGUI()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //************************************************* BAND ONE ***********************************************//
    // TYPE BAND ONE
    params.push_back(std::make_unique<juce::AudioParameterChoice>(BAND_ONE_ID,
                                                                  BAND_ONE_NAME,
                                                                  juce::StringArray("LPF","HPF"),0));
    //BAND ONE FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDONE_FREQ_ID,
                                                                 BANDONE_FREQ_NAME,
                                                                 50.0f,
                                                                 18000.0f,
                                                                 100.0f));
    //BAND ONE GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDONE_GAIN_ID,
                                                                 BANDONE_GAIN_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0f));
    //************************************************* BAND TWO ***********************************************//
    // TYPE TWO ONE
    params.push_back(std::make_unique<juce::AudioParameterChoice>(BAND_TWO_ID,
                                                                  BAND_TWO_NAME,
                                                                  juce::StringArray("LPF","HPF"),0));
    //BAND TWO FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDTWO_FREQ_ID,
                                                                 BANDTWO_FREQ_NAME,
                                                                 50.0f,
                                                                 10000.0f,
                                                                 5000.0f));
    //BAND TWO GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDTWO_GAIN_ID,
                                                                 BANDTWO_GAIN_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0f));
    //************************************************* BAND THREE ***********************************************//
    params.push_back(std::make_unique<juce::AudioParameterChoice>(BAND_THREE_ID,
                                                                  BAND_THREE_NAME,
                                                                  juce::StringArray("LPF","HPF"),0));
    //BAND TWO FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDTHREE_FREQ_ID,
                                                                 BANDTHREE_FREQ_NAME,
                                                                 50.0f,
                                                                 10000.0f,
                                                                 5000.0f));
    //BAND TWO GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDTHREE_GAIN_ID,
                                                                 BANDTHREE_GAIN_NAME,
                                                                 -60.0f,
                                                                 24.0f,
                                                                 0.0f));
    //************************************************* BAND FOUR ***********************************************//
    params.push_back(std::make_unique<juce::AudioParameterChoice>(BAND_FOUR_ID,
                                                                  BAND_FOUR_NAME,
                                                                  juce::StringArray("LPF","HPF"),0));
    //BAND TWO FREQ
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDFOUR_FREQ_ID,
                                                                 BANDFOUR_FREQ_NAME,
                                                                 50.0f,
                                                                 10000.0f,
                                                                 5000.0f));
    //BAND TWO GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>(BANDFOUR_GAIN_ID,
                                                                 BANDFOUR_GAIN_NAME,
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
        ptrBandOne[i]->prepare(sampleRate);
        ptrBandTwo[i]->prepare(sampleRate);
        ptrBandThree[i]->prepare(sampleRate);
        ptrBandFour[i]->prepare(sampleRate);
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

        ptrBandOne[channel]->process(channelData,
                                     channelData,
                                     buffer.getNumSamples(),
                                     *parameters.getRawParameterValue(BANDONE_FREQ_ID),
                                     *parameters.getRawParameterValue(BANDONE_GAIN_ID),
                                     EQ_Filters::FilterType::LPF);
        
        ptrBandTwo[channel]->process(channelData,
                                     channelData,
                                     buffer.getNumSamples(),
                                     *parameters.getRawParameterValue(BANDTWO_FREQ_ID),
                                     *parameters.getRawParameterValue(BANDTWO_GAIN_ID),
                                     EQ_Filters::FilterType::HPF);
        
        ptrBandThree[channel]->process(channelData,
                                     channelData,
                                     buffer.getNumSamples(),
                                     *parameters.getRawParameterValue(BANDTHREE_FREQ_ID),
                                     *parameters.getRawParameterValue(BANDTHREE_GAIN_ID),
                                     EQ_Filters::FilterType::HPF);
        
        ptrBandFour[channel]->process(channelData,
                                     channelData,
                                     buffer.getNumSamples(),
                                     *parameters.getRawParameterValue(BANDFOUR_FREQ_ID),
                                     *parameters.getRawParameterValue(BANDFOUR_GAIN_ID),
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
