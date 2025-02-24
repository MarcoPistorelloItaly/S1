/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 19 Jan 2025 11:25:43am
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NoiseGenerator.h"

//==============================================================================
NoiseGenerator::NoiseGenerator(S1AudioProcessor& p) :
processor(p)
{
    setSize(200, 200);

    switchButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, NOISE_GENERATOR_SWITCH_ID, switchButton);
    
    //switchButton.setRange(VOLUME_MIN, VOLUME_MAX);
    //switchButton.setButtonText(<#const String &newText#>)(Slider::TextBoxBelow, true, 100, 30);
    switchButton.addListener(this);
    addAndMakeVisible(&switchButton);
}

NoiseGenerator::~NoiseGenerator()
{
}

void NoiseGenerator::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("NoiseGenerator", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void NoiseGenerator::resized()
{
    const int ngWidth = 100;
    const int ngHeight = 100;
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    switchButton.setBounds(area.removeFromTop(ngWidth).removeFromLeft(ngHeight));
}

void NoiseGenerator::buttonClicked(juce::Button* button)
{
    if(button == &switchButton)
    {
        std::atomic<float>* switchParameter = processor.noiseGeneratorSwitchParameter;
        
        std::cout << "SWITCH Noise Generator" << " " << switchButton.getToggleState() << std::endl;
        switchParameter = new std::atomic<float>(switchButton.getToggleState());
    }
}

