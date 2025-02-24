/*
  ==============================================================================

    Mixer.h
    Created: 31 Dec 2024 11:52:11am
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ColorKnob.h"
#include "ImageButton.h"
#include "Constants.h"

//==============================================================================
/*
*/
class Mixer    : public juce::Component, public juce::Slider::Listener
{
public:
    Mixer(S1AudioProcessor&);
    ~Mixer();

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    juce::Slider level1Slider;
    juce::Slider level2Slider;
    S1AudioProcessor& processor;
    
    ImageButton button1;
    
    ColorKnob level1Knob;
    
    Constants constants;

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> level1SliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> level2SliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};
