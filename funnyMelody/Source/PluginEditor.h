#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FunnyMelodyAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public juce::Button::Listener
{
public:
    
    FunnyMelodyAudioProcessorEditor (FunnyMelodyAudioProcessor&);
    ~FunnyMelodyAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked (juce::Button* b) override;

private:
    
    juce::TextButton create;
    
    FunnyMelodyAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyMelodyAudioProcessorEditor)
};
