#pragma once
#include <JuceHeader.h>

class funnyDistortion
{
public:
    
    funnyDistortion();
    ~funnyDistortion();
    
    void process(float* inAudio,
                 float* outAudio,
                 int inNumSamples,
                 float inDrive,
                 float inRange,
                 float inBlend,
                 int inType);
    
};
