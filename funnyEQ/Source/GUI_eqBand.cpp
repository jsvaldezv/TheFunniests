#include "GUI_eqBand.h"

GUI_eqBand::GUI_eqBand(FunnyEQAudioProcessor& p, int inBand) : audioProcessor(p)
{
    setSize(WIDTH/4, HEIGHT/2);
    
    typeFilterCombo.addItem ("High Pass", 1);
    typeFilterCombo.addItem ("Low Pass", 2);
    typeFilterCombo.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(typeFilterCombo);
    
    auto band = BAND_ONE_ID;
    switch(inBand)
    {
        case 1:
            band = BAND_ONE_ID;
            break;
            
        case 2:
            band = BAND_TWO_ID;
            break;
            
        case 3:
            band = BAND_THREE_ID;
            break;
            
        case 4:
            band = BAND_FOUR_ID;
            break;
    }
    
    typeFilterComboAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters,
                                                                                                     band,
                                                                                                     typeFilterCombo);
}

GUI_eqBand::~GUI_eqBand(){}

void GUI_eqBand::paint (juce::Graphics& g)
{
    g.fillAll(backColor);
    
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (textBand, getLocalBounds(),
                juce::Justification::centred, true);
}

void GUI_eqBand::resized()
{
    typeFilterCombo.setBounds(getWidth()/2 - 50, 20, 100, 30);
}
