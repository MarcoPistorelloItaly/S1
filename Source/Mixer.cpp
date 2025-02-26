/*
  ==============================================================================

    Mixer.cpp
    Created: 31 Dec 2024 11:52:11am
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BinaryData.h"
#include "Mixer.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Mixer::Mixer(S1AudioProcessor& p) :
processor(p)
{
    level1Knob.setLookAndFeel(juce::ImageCache::getFromMemory(BinaryData::knob_silver_png, BinaryData::knob_silver_pngSize));
    
    level1SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, constants.getParamValueString(LEVEL_1_ID, "ID"), level1Slider);
    
    level1Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //level1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    level1Slider.setRange(constants.getParamValue(LEVEL_1_ID, "MIN"), constants.getParamValue(LEVEL_1_ID, "MAX"));
    level1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    
    addAndMakeVisible(&level1Slider);
    level1Slider.setLookAndFeel(&level1Knob);
    level1Slider.addListener(this);
    
    level2SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, constants.getParamValueString(LEVEL_2_ID, "ID"), level2Slider);
    
    addAndMakeVisible(&level2Slider);
    
    level2Slider.setLookAndFeel(&level1Knob);
    level2Slider.addListener(this);
    level2Slider.setRange(constants.getParamValue(LEVEL_2_ID, "MIN"), constants.getParamValue(LEVEL_2_ID, "MAX"));
    //level2Slider.setValue(processor.ampLeadMidKnobState);
    level2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    level2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    level2Slider.setNumDecimalPlacesToDisplay(1);
    level2Slider.setDoubleClickReturnValue(true, 0.0);
    
    setSize(200, 400);
}

Mixer::~Mixer()
{
}

void Mixer::paint (juce::Graphics& g)
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
    g.drawText ("Mixer", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Mixer::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(20);
    level1Slider.setBounds(area.removeFromLeft(50).removeFromTop(200));
    
    level2Slider.setBounds(area.removeFromLeft(50).removeFromTop(200));
    
    /*
    std::cout << "Mixer Reized" << std::endl;
    
    std::cout << area.getWidth() << " " << area.getX() << std::endl;
    
    std::cout << area.getHeight() << " " << area.getY() << std::endl;*/
}

void Mixer::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &level1Slider)
    {
        processor.level1Parameter = new std::atomic<float>(level1Slider.getValue());
    }
    
    if(slider == &level2Slider)
    {
        processor.level2Parameter = new std::atomic<float>(level2Slider.getValue());
    }
    
}

