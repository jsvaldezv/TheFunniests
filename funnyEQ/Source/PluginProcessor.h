#pragma once
#include <JuceHeader.h>
#include "EQ_Helper.h"
#include "EQ_Filters.h"

class FunnyEQAudioProcessor  : public juce::AudioProcessor
{
public:

    FunnyEQAudioProcessor();
    ~FunnyEQAudioProcessor() override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void initializeDSP();
    
    juce::AudioProcessorValueTreeState parameters;
    juce::AudioProcessorValueTreeState::ParameterLayout initializeGUI();
    
    void pushNextSampleIntoFifo (float* sample) noexcept;
    void drawNextFrameOfSpectrum();
    
    enum
    {
        fftOrder  = 11,
        fftSize   = 1 << fftOrder,
        scopeSize = 512
    };
    
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData [scopeSize];

private:
    
    std::unique_ptr<EQ_Filters> ptrBandOne[2];
    std::unique_ptr<EQ_Filters> ptrBandTwo[2];
    std::unique_ptr<EQ_Filters> ptrBandThree[2];
    std::unique_ptr<EQ_Filters> ptrBandFour[2];
    
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyEQAudioProcessor)
};
