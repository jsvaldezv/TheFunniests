#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI_Helper.h"
#include "EQ_Helper.h"

class GUI_eqBand  : public juce::Component
{
    
public:
    
    GUI_eqBand(FunnyEQAudioProcessor&, int inBand);
    ~GUI_eqBand() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setTextBand(juce::String inText){textBand = inText;};
    void setColorBand(juce::Colour inColor){backColor = inColor;};

private:
    
    juce::String textBand;
    juce::Colour backColor;
    
    juce::ComboBox typeFilterCombo;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeFilterComboAttach;
    
    juce::Slider freqSlider;
    juce::Slider gainSlider;
    
    FunnyEQAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI_eqBand)
};
