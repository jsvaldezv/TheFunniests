#include "EQ_LowPass.h"

EQ_LowPass::EQ_LowPass(){}

EQ_LowPass::~EQ_LowPass(){}

void EQ_LowPass::prepareLowPass(float inSampleRate)
{
    sampleRate = inSampleRate;
}

void EQ_LowPass::processLowPass(float* inAudio,
                                float* outAudio,
                                int inNumSamples,
                                float inFrequency,
                                float inGain)
{
    if(frequency != inFrequency || gain != inGain)
    {
        inGain = juce::Decibels::decibelsToGain(inGain, -100.0f);
        
        frequency = inFrequency;
        gain = inGain;
        
        float w0 = (2.0f * VALOR_PI) * frequency / sampleRate;
        float alpha = sin(w0) / (2.0f * gain);
        float cw0 = cos(w0);
        
        a0 = 1.0f + alpha;
        a1 = (-2.0f * cw0);
        a2 = (1.0f - alpha);
        
        b0 = (1.0f - cw0) / 2.0f;
        b1 = 1.0f - cw0;
        b2 = b0;
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
