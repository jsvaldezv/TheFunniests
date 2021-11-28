#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "funnyLookAndFeel.h"

class FunnyDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    FunnyDistortionAudioProcessorEditor (FunnyDistortionAudioProcessor&);
    ~FunnyDistortionAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void paintGUI();

private:

    juce::Image backgroundImage;
    juce::ImageComponent background;
    
    funnyLookAndFeel funnyLookAndFeel;
    
    juce::Slider sliderDrive;
    juce::Slider sliderRange;
    juce::Slider sliderBlend;
    juce::Slider sliderVolume;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  driveAttachment,
                                                                            rangeAttachment,
                                                                            blendAttachment,
                                                                            volAttachment;

    juce::Label slDrive;
    juce::Label slRange;
    juce::Label slBlend;
    juce::Label slVolume;
    juce::Label mainText;
    
    juce::ComboBox cChoice;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> choiceAttachment;
    
    FunnyDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunnyDistortionAudioProcessorEditor)
};
