/*
  ==============================================================================

    SynthEngine.cpp
    Created: 4 Jan 2025 2:58:59pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthEngine.h"

//==============================================================================
SynthEngine::SynthEngine(S1AudioProcessor& p, int index) :
processor(p), oscillator(p, index), adsr(p, index), distortion(p, index), filter(p, index)
{
    setSize(1200, 200);
    
    addAndMakeVisible(&oscillator);
    
    addAndMakeVisible(&adsr);
    
    addAndMakeVisible(&distortion);
    
    addAndMakeVisible(&filter);
    
    indexParam = index;
}

SynthEngine::~SynthEngine()
{
}

void SynthEngine::paint (juce::Graphics& g)
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
    g.drawText ("Synth Engine ", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SynthEngine::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    
    /*
    std::cout << "Synth Engine Resized " << indexParam << " " << std::endl;
    std::cout << area.getWidth() << " " << area.getHeight() << std::endl;
    std::cout << area.getX() << " " << area.getY() << std::endl;
    */
    const int oscWidth = 250;
    const int oscHeight = 250;
    oscillator.setBounds(area.removeFromLeft(oscWidth).removeFromTop(oscHeight));
    
    const int adsrWidth = 250;
    const int adsrHeight = 200;
    adsr.setBounds(area.removeFromLeft(adsrWidth).removeFromTop(adsrHeight));
    
    const int distortionWidth = 200;
    const int distortionHeight = 200;
    distortion.setBounds(area.removeFromLeft(distortionWidth).removeFromTop(distortionHeight));
    
    const int filterWidth = 500;
    const int filterHeight = 200;
    filter.setBounds(area.removeFromLeft(filterWidth).removeFromTop(filterHeight));
    
}

