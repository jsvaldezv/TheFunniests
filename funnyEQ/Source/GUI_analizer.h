#pragma once
#include <JuceHeader.h>
#include "GUI_Helper.h"

class GUI_analizer  : public juce::Component
{
public:
    GUI_analizer();
    ~GUI_analizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI_analizer)
};
