#include "funnyVolume.h"

funnyVolumen::funnyVolumen(){}

funnyVolumen::~funnyVolumen(){}

void funnyVolumen::process(float* inAudio, float* outAudio, float inVolumen, int inNumSamplesToRender)
{
    inVolumen = juce::Decibels::decibelsToGain(inVolumen, -100.0f);
    
    //CICLANDO LAS MUESTRAS PARA QUE LE AFECTE EL SLIDER DE VOLUMEN
    for(int i = 0; i < inNumSamplesToRender; i++)
    {
        volumenSmooth = volumenSmooth - 0.002f * (volumenSmooth - inVolumen);
        outAudio[i] = inAudio[i] * volumenSmooth;
    }
}
