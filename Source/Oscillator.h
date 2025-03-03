/*
  ==============================================================================

    Oscillator.h
    Created: 4 Jan 2025 3:03:39pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"
#include "PluginProcessor.h"
#include "Utilities.h"


//==============================================================================
/*
*/
class Oscillator    : public juce::Component,
                        private juce::ComboBox::Listener,
                        private juce::Button::Listener,
                        public juce::Slider::Listener
{
public:
    Oscillator(S1AudioProcessor&, int);
    ~Oscillator();

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged (juce::ComboBox*) override;
    
    void buttonClicked (juce::Button*) override;
    
    juce::ImageButton button1;
    
    int currentWaveType = 0;
    
    juce::Image image;
    
    juce::Image oscillatorImage;
    
    void sliderValueChanged(juce::Slider* slider) override;

private:

    juce::ComboBox oscMenu;
    
    S1AudioProcessor& processor;
    
    Utilities utilities;
    
    juce::Slider levelSlider;
    
    int index;
    
    juce::Label volumeLabel;
    
    Constants constants;


public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveTypeComboBoxAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
