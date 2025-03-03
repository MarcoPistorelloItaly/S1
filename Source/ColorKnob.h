/*
  ==============================================================================

    ColorKnob.h
    Created: 31 Dec 2024 11:53:27am
    Author:  Marco

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
class ColorKnob : public juce::LookAndFeel_V4
{

public:
    ColorKnob();
    void setLookAndFeel(juce::Image inputImage);
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image img;

};
