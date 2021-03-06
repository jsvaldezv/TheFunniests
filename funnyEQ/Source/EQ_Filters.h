#pragma once
#include <JuceHeader.h>
#include "EQ_Helper.h"
#include "math.h"

class EQ_Filters
{
public:
    
    enum FilterType
    {
        LPF,
        HPF,
        BELL,
        NOTCH
    };
    
    EQ_Filters(FilterType inFilterType);
    ~EQ_Filters();
    
    void prepare(double inSampleRate);
    
    void process(float* inAudio,
                 float* outAudio,
                 int inNumSamples,
                 float inFrequency,
                 float inGain,
                 int inFilterType);
    
    void updateCoefficients(int inFilterType);

private:
    
    int myFilterType = LPF;
    
    float sampleRate{0.0f}, frequency{200.0f}, gain {0.1f}, A{0.0f};
    
    float x1{0.0f}, x2{0.0f}, y1{0.0f}, y2{0.0f};
    
    float w0{0.0f}, alpha{0.0f}, cw0{0.0f};
    
    float b0 {1.0f}, b1{0.0f}, b2{0.0f};
    float a0 {1.0f}, a1{0.0f}, a2{0.0f};
};
