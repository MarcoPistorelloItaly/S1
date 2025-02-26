/*
  ==============================================================================

    Adsr.cpp
    Created: 4 Jan 2025 3:00:17pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Adsr.h"
#include "Constants.h"

//#include "filter_selector.h"

//==============================================================================
Adsr::Adsr(S1AudioProcessor& p, int index) :
processor(p)
{
    
    std::string attackId = ADSR_1_ATTACK_ID;
    if(index == 2) {
        attackId = ADSR_2_ATTACK_ID;
    }
    
    std::string decayId = ADSR_1_DECAY_ID;
    if(index == 2) {
        decayId = ADSR_2_DECAY_ID;
    }
    
    std::string sustainId = ADSR_1_SUSTAIN_ID;
    if(index == 2) {
        sustainId = ADSR_2_SUSTAIN_ID;
    }
    
    std::string releaseId = ADSR_1_RELEASE_ID;
    if(index == 2) {
        releaseId = ADSR_2_RELEASE_ID;
    }
    
    float adsrAttackMinFloat = constants.getParamValue(attackId, "MIN");
    float adsrAttackMaxFloat = constants.getParamValue(attackId, "MAX");
    
    float adsrDecayMinFloat = constants.getParamValue(decayId, "MIN");
    float adsrDecayMaxFloat = constants.getParamValue(decayId, "MAX");
    
    float adsrSustainMinFloat = constants.getParamValue(sustainId, "MIN");
    float adsrSustainMaxFloat = constants.getParamValue(sustainId, "MAX");
    
    float adsrReleaseMinFloat = constants.getParamValue(releaseId, "MIN");
    float adsrReleaseMaxFloat = constants.getParamValue(releaseId, "MAX");
    
    attackLabel.setName("AttackLabel");
    attackLabel.setText ("A", juce::dontSendNotification);
    attackLabel.setFont(FONT_SIZE_1);
    attackLabel.setBounds(50, 35, 50, 100);
    attackLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible (attackLabel);
    
    decayLabel.setText ("D", juce::dontSendNotification);
    decayLabel.setFont(FONT_SIZE_1);
    decayLabel.setBounds(100, 35, 50, 100);
    decayLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible (decayLabel);
    
    sustainLabel.setText ("S", juce::dontSendNotification);
    sustainLabel.setFont(FONT_SIZE_1);
    sustainLabel.setBounds(150, 35, 50, 100);
    sustainLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible (sustainLabel);
    
    releaseLabel.setText ("R", juce::dontSendNotification);
    releaseLabel.setFont(FONT_SIZE_1);
    releaseLabel.setBounds(200, 35, 50, 100);
    releaseLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible (releaseLabel);
    
    adsrLabel.setText("AAAA", juce::dontSendNotification);

    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, attackId, attackSlider);
    
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(adsrAttackMinFloat, adsrAttackMaxFloat);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    attackSlider.addListener(this);
    attackSlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&attackSlider);
    
    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, decayId, decaySlider);
    
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(adsrDecayMinFloat, adsrDecayMaxFloat);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    decaySlider.addListener(this);
    decaySlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&decaySlider);
    
    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, sustainId, sustainSlider);
    
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(adsrSustainMinFloat, adsrSustainMaxFloat);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    sustainSlider.addListener(this);
    sustainSlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&sustainSlider);
    
    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, releaseId, releaseSlider);
    
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(adsrReleaseMinFloat, adsrReleaseMaxFloat);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    releaseSlider.addListener(this);
    releaseSlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&releaseSlider);
    
    //setSize(200, 200);
    
    indexParam = index;
}

Adsr::~Adsr()
{
}

void Adsr::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::grey);
    g.setFont (FONT_SIZE_1);
    
    montserrat.setTypefaceName("Montserrat");
    g.setFont(montserrat);
    g.drawText ("ADSR", getLocalBounds().reduced(10),
                juce::Justification::topLeft, true);   // draw some placeholder text
}

void Adsr::resized()
{
    juce::Rectangle<int> area = getLocalBounds();//.reduced(20);
    area.setPosition(50, 0);
    attackSlider.setBounds(area.removeFromLeft(50).removeFromTop(300));
    decaySlider.setBounds(area.removeFromLeft(50).removeFromTop(300));
    sustainSlider.setBounds(area.removeFromLeft(50).removeFromTop(300));
    releaseSlider.setBounds(area.removeFromLeft(50).removeFromTop(300));
    
}

void Adsr::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &attackSlider)
    {
        std::atomic<float>* attackParameter = processor.attack1Parameter;
        
        if(indexParam == 2) {
            attackParameter = processor.attack2Parameter;
        }
        
        attackParameter = new std::atomic<float>(attackSlider.getValue());
    }
    
    if(slider == &decaySlider)
    {
        std::atomic<float>* decayParameter = processor.decay1Parameter;
        
        if(indexParam == 2) {
            decayParameter = processor.decay2Parameter;
        }
        
        decayParameter = new std::atomic<float>(decaySlider.getValue());
    }
    
    if(slider == &sustainSlider)
    {
        std::atomic<float>* sustainParameter = processor.sustain1Parameter;
        
        if(indexParam == 2) {
            sustainParameter = processor.sustain2Parameter;
        }
        
        sustainParameter = new std::atomic<float>(sustainSlider.getValue());
    }
    
    if(slider == &releaseSlider)
    {
        //std::atomic<float>* releaseParameter = processor.release1Parameter;
        
        if(indexParam == 2) {
            //releaseParameter = processor.release2Parameter;
        }
        
        //std::cout << "Release Slider " << indexParam << " " << releaseSlider.getValue() << std::endl;
        //releaseParameter = new std::atomic<float>(releaseSlider.getValue());
    }
    
}

void Adsr::mouseEnter(const juce::MouseEvent &event)

{
    DBG("A");

}

void Adsr::mouseExit(const juce::MouseEvent &event)

{
    DBG("B");
    //event.eventComponent->removeAllChildren();
    
}

