/*
  ==============================================================================

    Adsr.h
    Created: 4 Jan 2025 3:00:17pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"

//==============================================================================
/*
*/
class Adsr    : public juce::Component,
                public juce::Slider::Listener
{
public:
    Adsr(S1AudioProcessor&, int);
    ~Adsr();

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    S1AudioProcessor& processor;
    
    int indexParam;
    
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    
    juce::Label adsrLabel;
    juce::Font montserrat;
    
    Constants constants;
    
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sustainSliderAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;
    
    void mouseEnter(const juce::MouseEvent &event);
    void mouseExit(const juce::MouseEvent &event);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Adsr)
};

