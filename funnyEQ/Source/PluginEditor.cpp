#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyEQAudioProcessorEditor::FunnyEQAudioProcessorEditor (FunnyEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

FunnyEQAudioProcessorEditor::~FunnyEQAudioProcessorEditor(){}

void FunnyEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Funny EQ", getLocalBounds(), juce::Justification::centred, 1);
}

void FunnyEQAudioProcessorEditor::resized(){}
