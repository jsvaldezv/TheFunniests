#pragma once
#include <JuceHeader.h>
#include "EQ_Helper.h"
#include "math.h"

class EQ_HighPass
{

public:
    
    EQ_HighPass();
    ~EQ_HighPass();
    
    void prepareHighPass(float inSampleRate);
    
    void processHighPass(float* inAudio,
                         float* outAudio,
                         int inNumSamples,
                         float inFrequency,
                         float inGain);
    
private:
    
    float sampleRate{0.0f}, frequency{200.0f}, gain {0.1f};
    
    float x1{0.0f}, x2{0.0f}, y1{0.0f}, y2{0.0f};
    
    float b0 {1.0f}, b1{0.0f}, b2{0.0f};
    float a0 {1.0f}, a1{0.0f}, a2{0.0f};
    
};
