#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI_Helper.h"
#include "GUI_eqBand.h"
#include "GUI_analizer.h"

class FunnyEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FunnyEQAudioProcessorEditor (FunnyEQAudioProcessor&);
    ~FunnyEQAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    GUI_eqBand bandOne, bandTwo, bandThree, bandFour;
    
    GUI_analizer myAnalizer;
    
    FunnyEQAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyEQAudioProcessorEditor)
};
