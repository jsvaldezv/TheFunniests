#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyDistortionAudioProcessorEditor::FunnyDistortionAudioProcessorEditor (FunnyDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);
    
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::bulbo_png, BinaryData::bulbo_pngSize);
    background.setImage(backgroundImage, juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(background);
    
    setLookAndFeel(&funnyLookAndFeel);
    
    paintGUI();
}

FunnyDistortionAudioProcessorEditor::~FunnyDistortionAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void FunnyDistortionAudioProcessorEditor::paint (juce::Graphics& g){}

void FunnyDistortionAudioProcessorEditor::resized()
{
    background.setBounds(0, 0, getWidth(), getHeight());
    
    sliderVolume.setBounds(210, 250, 90, 90);
    sliderDrive.setBounds(60, 110, 90, 90);
    sliderRange.setBounds(210, 110, 90, 90);
    sliderBlend.setBounds(60, 250, 90, 90);
    
    cChoice.setBounds(85, 20, 200, 35);
}

void FunnyDistortionAudioProcessorEditor::paintGUI()
{
    //**********************************************************************************************
        
    //VOLUME
    sliderVolume.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderVolume.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderVolume);
    
    volAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,
                                                                                            VOLUME_ID,
                                                                                            sliderVolume);
    
    //ETIQUETA
    addAndMakeVisible (slVolume);
    slVolume.setText ("Volume", juce::dontSendNotification);
    slVolume.attachToComponent (&sliderVolume, true);
    slVolume.setColour (juce::Label::textColourId, juce::Colours::white);
    slVolume.setCentrePosition(255, 240);
        
    //**********************************************************************************************
    //DRIVE
    sliderDrive.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderDrive.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderDrive);
    
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,
                                                                                              DRIVE_ID,
                                                                                              sliderDrive);

    //ETIQUETA
    addAndMakeVisible (slDrive);
    slDrive.setText ("Drive", juce::dontSendNotification);
    slDrive.attachToComponent (&sliderDrive, true);
    slDrive.setColour (juce::Label::textColourId, juce::Colours::white);
    slDrive.setCentrePosition(105, 95);
        
    //**********************************************************************************************
    //RANGE
    sliderRange.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderRange.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderRange);
    
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,
                                                                                              RANGE_ID,
                                                                                              sliderRange);
    
    //ETIQUETA
    addAndMakeVisible (slRange);
    slRange.setText ("Range", juce::dontSendNotification);
    slRange.attachToComponent (&sliderRange, true);
    slRange.setColour (juce::Label::textColourId, juce::Colours::white);
    slRange.setCentrePosition(255, 95);

    //**********************************************************************************************
    //BLEND
    sliderBlend.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderBlend.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    addAndMakeVisible(sliderBlend);
    
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters,
                                                                                              BLEND_ID,
                                                                                              sliderBlend);
    
    //ETIQUETA
    addAndMakeVisible (slBlend);
    slBlend.setText ("Blend", juce::dontSendNotification);
    slBlend.attachToComponent (&sliderBlend, true);
    slBlend.setColour (juce::Label::textColourId, juce::Colours::white);
    slBlend.setCentrePosition(105, 240);

    //**********************************************************************************************
    //COMBOBOX
    cChoice.setColour(juce::ComboBox::backgroundColourId, juce::Colours::black);
    cChoice.setColour(juce::ComboBox::outlineColourId, juce::Colours::ghostwhite);
    cChoice.setColour(juce::ComboBox::arrowColourId, juce::Colours::ghostwhite);
    cChoice.setColour(juce::ComboBox::textColourId, juce::Colours::ghostwhite);
    cChoice.addItem ("Something Broken", 1);
    cChoice.addSeparator();
    cChoice.addItem ("Television", 2);
    cChoice.addSeparator();
    cChoice.addItem ("Intercepted Transmission", 3);
    cChoice.addSeparator();
    addAndMakeVisible (cChoice);
    
    choiceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters,
                                                                                                 TYPE_ID,
                                                                                                 cChoice);
}
