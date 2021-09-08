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
    
    /*enum
    {
        fftOrder  = 11,
        fftSize   = 1 << fftOrder,
        scopeSize = 512
    };*/

private:
    
    /*juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;
 
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData [scopeSize];*/
    
    FunnyEQAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI_analizer)
};
