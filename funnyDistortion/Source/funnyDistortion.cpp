#include "funnyDistortion.h"

funnyDistortion::funnyDistortion(){}

funnyDistortion::~funnyDistortion(){}

void funnyDistortion::process(float* inAudio,
                              float* outAudio,
                              int inNumSamples,
                              float inDrive,
                              float inRange,
                              float inBlend,
                              int inType)
{
    inDrive = juce::jmap(inDrive, 0.0001f, 1.0f, -24.0f, 24.0f);
    inDrive = juce::Decibels::decibelsToGain(inDrive, -24.0f);
    
    float inputGain = powf(10.0f, inDrive / 20.f);
    
    for (int i = 0; i < inNumSamples; i++)
    {
        float cleanSample = inAudio[i];
        float in = inputGain * inAudio[i];
        
        if (inType == 0)
        {
            //HALF WAVE RECTIFIER
            if (in > 0)
            {
                inAudio[i] = in * inBlend;
                inAudio[i] += (cleanSample * (1.f / inBlend)) / 2;
            }
            
            else
            {
                inAudio[i] = 0;
                inAudio[i] += (cleanSample * (1.f / inBlend)) / 2;
            }
        }
        else if(inType == 1)
        {
            //FULL WAVE RECTIFIER
            inAudio[i] = fabs(in) * inBlend;
            inAudio[i] += (cleanSample * (1.f / inBlend)) / 2;
        }
        else
        {
            //SUPER FAT
            inAudio[i] *= inDrive * inRange;
            inAudio[i] = ((((2.f / M_PI) * (atan(inAudio[i]))) * inBlend));
            inAudio[i] += (cleanSample * (1.f / inBlend)) / 2;
            inAudio[i] *= 0.25;
        }
        
        outAudio[i] = inAudio[i];
    }
}


