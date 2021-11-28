#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class FunnyDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    FunnyDistortionAudioProcessorEditor (FunnyDistortionAudioProcessor&);
    ~FunnyDistortionAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Image backgroundImage;
    juce::ImageComponent background;
    
    FunnyDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyDistortionAudioProcessorEditor)
};
