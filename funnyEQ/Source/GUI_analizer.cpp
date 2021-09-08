#include <JuceHeader.h>
#include "GUI_analizer.h"

GUI_analizer::GUI_analizer()
{
    setSize(WIDTH, HEIGHT/2);
}

GUI_analizer::~GUI_analizer(){}

void GUI_analizer::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    
    g.setColour (juce::Colours::black);
    g.setFont (14.0f);
    g.drawText ("ANALIZER", getLocalBounds(),
                juce::Justification::centred, true);
}

void GUI_analizer::resized(){}
