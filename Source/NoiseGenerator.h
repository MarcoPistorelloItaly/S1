/*
  ==============================================================================

    NoiseGenerator.h
    Created: 19 Jan 2025 11:25:43am
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#define NOISE_GENERATOR_SWITCH_ID "noiseGeneratorSwitchParameter"
#define NOISE_GENERATOR_SWITCH_NAME "noiseGeneratorSwitchParameter"

//==============================================================================
/*
*/
class NoiseGenerator    : public juce::Component,
public juce::Button::Listener
{
public:
    NoiseGenerator(S1AudioProcessor&);
    ~NoiseGenerator();

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:

    juce::ToggleButton switchButton;
    
    S1AudioProcessor& processor;


public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> switchButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGenerator)
};
