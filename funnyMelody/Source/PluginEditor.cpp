#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyMelodyAudioProcessorEditor::FunnyMelodyAudioProcessorEditor (FunnyMelodyAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    create.setClickingTogglesState(false);
    create.setButtonText("Create Melody");
    create.addListener(this);
    create.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::blue);
    addAndMakeVisible(create);
}

FunnyMelodyAudioProcessorEditor::~FunnyMelodyAudioProcessorEditor(){}

void FunnyMelodyAudioProcessorEditor::buttonClicked (juce::Button* b)
{
    if(b == &create)
        audioProcessor.createMelody(10);
}

void FunnyMelodyAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Funny Melody", getLocalBounds(), juce::Justification::centred, 1);
}

void FunnyMelodyAudioProcessorEditor::resized()
{
    create.setBounds(getWidth()/2 - 50, getHeight()/2 - 15, 100, 30);
}
