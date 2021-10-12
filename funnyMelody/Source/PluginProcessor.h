#pragma once
#include <JuceHeader.h>

#include <clasp/enumerator.h>
#include <clasp/solver.h>
#include <clasp/logic_program.h>
#include <clasp/model_enumerators.h>
#include <clasp/solve_algorithms.h>

#if JUCE_WINDOWS
    static const juce::String directorySeparator = "\\";
#elif JUCE_MAC
    static const juce::String directorySeparator = "/";
#endif

class FunnyMelodyAudioProcessor  : public juce::AudioProcessor
{
public:

    FunnyMelodyAudioProcessor();
    ~FunnyMelodyAudioProcessor() override;

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
    
    // CREATE MELODY //
    void createMelody (int noteNumber);
    
    // CLINGO ASP //
    void printModel(const Clasp::OutputTable& out, const Clasp::Model& model);
    void example1(bool basicSolve);

private:
    
    juce::String name = "Melody";
    juce::String extension = ".mid";
    
    int numMelody{0};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyMelodyAudioProcessor)
};
