#pragma once
#include <JuceHeader.h>
#include "funnyNames.h"
#include "funnyDistortion.h"
#include "funnyVolume.h"

class FunnyDistortionAudioProcessor  : public juce::AudioProcessor
{
public:

    FunnyDistortionAudioProcessor();
    ~FunnyDistortionAudioProcessor() override;

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
    
    juce::AudioProcessorValueTreeState parameters;
    juce::AudioProcessorValueTreeState::ParameterLayout initializeGUI();

private:
    
    std::unique_ptr<funnyDistortion> ptrDistor[4];
    std::unique_ptr<funnyVolumen> ptrVolume[4];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyDistortionAudioProcessor)
};
