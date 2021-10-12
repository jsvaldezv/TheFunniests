#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyEQAudioProcessorEditor::FunnyEQAudioProcessorEditor (FunnyEQAudioProcessor& p)
: AudioProcessorEditor (&p), bandOne(p, 1), bandTwo(p, 2), bandThree(p, 3), bandFour(p, 4), myAnalizer(p), audioProcessor (p)
{
    setSize (WIDTH, HEIGHT);
    
    addAndMakeVisible(myAnalizer);
    
    bandOne.setTextBand("Band One");
    bandOne.setColorBand(juce::Colours::red);
    addAndMakeVisible(bandOne);
    
    bandTwo.setTextBand("Band Two");
    bandTwo.setColorBand(juce::Colours::blue);
    addAndMakeVisible(bandTwo);
    
    bandThree.setTextBand("Band Three");
    bandThree.setColorBand(juce::Colours::green);
    addAndMakeVisible(bandThree);
    
    bandFour.setTextBand("Band Four");
    bandFour.setColorBand(juce::Colours::purple);
    addAndMakeVisible(bandFour);
}

FunnyEQAudioProcessorEditor::~FunnyEQAudioProcessorEditor(){}

void FunnyEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Funny EQ", getLocalBounds(), juce::Justification::centred, 1);
}

void FunnyEQAudioProcessorEditor::resized()
{
    myAnalizer.setBounds(0, 0, myAnalizer.getWidth(), myAnalizer.getHeight());
    
    bandOne.setBounds(0, HEIGHT/2, bandOne.getWidth(), bandOne.getHeight());
    bandTwo.setBounds(WIDTH/4, HEIGHT/2, bandOne.getWidth(), bandOne.getHeight());
    bandThree.setBounds(WIDTH/2, HEIGHT/2, bandOne.getWidth(), bandOne.getHeight());
    bandFour.setBounds(WIDTH/4 * 3, HEIGHT/2, bandOne.getWidth(), bandOne.getHeight());
}
