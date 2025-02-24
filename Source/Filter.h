/*
  ==============================================================================

    Filter.h
    Created: 4 Jan 2025 3:14:04pm
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
class Filter    : public juce::Component,
                    public juce::Slider::Listener,
                    public juce::ComboBox::Listener,
                    public juce::Button::Listener
{
public:
    Filter(S1AudioProcessor&, int);
    ~Filter();

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged (juce::ComboBox*) override;
    void buttonClicked(juce::Button* button) override;

private:
    juce::Slider filterCutoffDialSlider;
    juce::Slider filterResDialSlider;
    juce::Slider filterAttackDialSlider;
    juce::ComboBox filterMenu;
    S1AudioProcessor& processor;
    int index;
    juce::ToggleButton switchButton;
    juce::ImageButton filterTypeButton;
    Utilities utilities;
    int currentFilterType = 0;
    
    juce::Label filterCutOffLabel;
    juce::Label filterResLabel;
    juce::Label filterAttackLabel;
    
    Constants constants;

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffDialAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> filterResDialAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> filterAttackDialAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> switchButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
