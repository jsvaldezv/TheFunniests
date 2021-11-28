#pragma once
#include <JuceHeader.h>

class funnyVolumen
{
public:
    
    funnyVolumen();
    ~funnyVolumen();
    
    void process(float* inAudio, float* outAudio, float inVolumen, int inNumSamplesToRender);
    
private:
    
    float volumenSmooth{0.0f};
    
};
