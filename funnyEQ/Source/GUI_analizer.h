#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI_Helper.h"

class GUI_analizer  : public juce::Component,
                      public juce::Timer
{
public:
    
    GUI_analizer(FunnyEQAudioProcessor&);
    ~GUI_analizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    
    FunnyEQAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI_analizer)
};
