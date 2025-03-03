/*
  ==============================================================================

    ImageButton.h
    Created: 31 Dec 2024 11:56:34am
    Author:  Marco

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
class ImageButton : public juce::LookAndFeel_V4
{

public:
    ImageButton();
    void setLookAndFeel(juce::Image inputImage);
    
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
    void drawImageButton (juce::Graphics &, juce::Image *, int imageX, int imageY, int imageW, int imageH, const juce::Colour &overlayColour, float imageOpacity, ImageButton imageButton);
    
    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    juce::Image img;
};
