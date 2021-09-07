#include "EQ_Filters.h"

EQ_Filters::EQ_Filters(FilterType inFilterType) : myFilterType(inFilterType)
{
    updateCoefficients(inFilterType);
}

EQ_Filters::~EQ_Filters(){}

void EQ_Filters::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
}

void EQ_Filters::process(float* inAudio,
                         float* outAudio,
                         int inNumSamples,
                         float inFrequency,
                         float inGain,
                         FilterType inFilterType)
{
    if(frequency != inFrequency || gain != inGain)
    {
        inGain = juce::Decibels::decibelsToGain(inGain, -100.0f);
        
        frequency = inFrequency;
        gain = inGain;
        updateCoefficients(inFilterType);
    }
    
    for(int i = 0; i < inNumSamples; i++)
    {
        float y = (b0 / a0) * inAudio[i] + (b1 / a0) * x1 + (b2 / a0) * x2 + (-a1/a0) * y1 + (-a2/a0) * y2;
        
        x2 = x1;
        x1 = inAudio[i];
        y2 = y1;
        y1 = y;
        
        outAudio[i] = y;
    }
}

void EQ_Filters::updateCoefficients(FilterType inFilter)
{
    myFilterType = inFilter;
    
    switch(myFilterType)
    {
        case LPF:
            
            w0 = (2.0f * VALOR_PI) * frequency / sampleRate;
            alpha = sin(w0) / (2.0f * gain);
            cw0 = cos(w0);
            
            a0 = 1.0f + alpha;
            a1 = (-2.0f * cw0);
            a2 = (1.0f - alpha);
            
            b0 = (1.0f - cw0) / 2.0f;
            b1 = 1.0f - cw0;
            b2 = b0;
            
            break;
            
        case HPF:
            
            w0 = (2.0f * VALOR_PI) * frequency / sampleRate;
            alpha = sin(w0) / (2.0f * gain);
            cw0 = cos(w0);
            
            a0 = 1.0f + alpha;
            a1 = (-2.0f * cw0);
            a2 = (1.0f - alpha);
            
            b0 = (1.0f + cw0) / 2.0f;
            b1 = -(1.0f + cw0);
            b2 = b0;
            
            break;
    }
}
