#pragma once
#include <JuceHeader.h>

class funnyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    funnyLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        juce::Path p;
        auto pointerLength = radius * 0.5f;
        auto pointerThickness = 6.0f;
        
        // fill
        //g.setColour(juce::Colour(46, 44, 47));
        g.setColour(juce::Colour(67, 67, 75));
        g.fillEllipse(rx, ry, rw, rw);
        
        // outline
        g.setColour(juce::Colours::whitesmoke);
        g.drawEllipse(rx, ry, rw, rw, 1.0f);
        
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        
        // pointer
        g.setColour(juce::Colours::red);
        g.fillPath(p);
        
    }
};
