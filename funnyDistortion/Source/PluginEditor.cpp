#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyDistortionAudioProcessorEditor::FunnyDistortionAudioProcessorEditor (FunnyDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);
    
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::bulbo_png, BinaryData::bulbo_pngSize);
    background.setImage(backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(background);
}

FunnyDistortionAudioProcessorEditor::~FunnyDistortionAudioProcessorEditor(){}

void FunnyDistortionAudioProcessorEditor::paint (juce::Graphics& g){}

void FunnyDistortionAudioProcessorEditor::resized()
{
    background.setBounds(0, 0, getWidth(), getHeight());
}
