#include <JuceHeader.h>
#include "GUI_analizer.h"

GUI_analizer::GUI_analizer(FunnyEQAudioProcessor& p) : audioProcessor(p)
{
    setSize(WIDTH, HEIGHT/2);
    startTimerHz(60);
}

GUI_analizer::~GUI_analizer()
{
    stopTimer();
}

void GUI_analizer::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    
    g.setColour(juce::Colours::black);
    
    for (int i = 1; i < audioProcessor.scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine ({ (float) juce::jmap (i -1, 0, audioProcessor.scopeSize - 1, 0, width),
                              juce::jmap (audioProcessor.scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) juce::jmap (i, 0, audioProcessor.scopeSize - 1, 0, width),
                              juce::jmap (audioProcessor.scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
    }
    
}

void GUI_analizer::resized(){}

void GUI_analizer::timerCallback()
{
    if (audioProcessor.nextFFTBlockReady)
    {
        audioProcessor.drawNextFrameOfSpectrum();
        audioProcessor.nextFFTBlockReady = false;
        repaint();
    }
}
