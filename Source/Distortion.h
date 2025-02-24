/*
  ==============================================================================

    Distortion.h
    Created: 4 Jan 2025 3:09:43pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utilities.h"
#include "Constants.h"

//==============================================================================
/*
*/
class Distortion    : public juce::Component,
                        public juce::Slider::Listener,
                        public juce::Button::Listener
{
public:
    Distortion(S1AudioProcessor&, int);
    ~Distortion();

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples);

private:
    juce::Slider driveSlider;
    juce::Slider rangeSlider;
    juce::Slider blendSlider;
    //Slider volumeSlider;
    juce::ToggleButton switchButton;
    S1AudioProcessor& processor;
    
    juce::Colour colourDriveSlider;
    juce::Colour colourRangeSlider;
    juce::Colour colourBlendSlider;
    //Colour colourVolumeSlider;
    
    int index;
    
    Utilities utilities;
    
    juce::Label driveLabel;
    juce::Label rangeLabel;
    
    Constants constants;

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> rangeSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> blendSliderAttachment;
    //std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> volumeSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> switchButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};
