/*
  ==============================================================================

    Distortion.cpp
    Created: 4 Jan 2025 3:09:43pm
    Author:  Marco

  ==============================================================================
*/

#include "Distortion.h"

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(S1AudioProcessor& p, int indexParam) :
processor(p)
{
    
    index = indexParam;
    
    juce::String driveId = constants.getParamValueString(DISTORTION_1_DRIVE_ID, "ID");
    float driveMin = constants.getParamValue(DISTORTION_1_DRIVE_ID, "MIN");
    float driveMax = constants.getParamValue(DISTORTION_1_DRIVE_ID, "MAX");
    if(indexParam == 2) {
        driveId = constants.getParamValueString(DISTORTION_2_DRIVE_ID, "ID");
        float driveMin = constants.getParamValue(DISTORTION_2_DRIVE_ID, "MIN");
        float driveMax = constants.getParamValue(DISTORTION_2_DRIVE_ID, "MAX");
    }
    
    juce::String rangeId = constants.getParamValueString(DISTORTION_1_RANGE_ID, "ID");
    if(indexParam == 2) {
        rangeId = constants.getParamValueString(DISTORTION_2_RANGE_ID, "ID");
    }
    
    juce::String blendId = constants.getParamValueString(DISTORTION_1_BLEND_ID, "ID");
    if(indexParam == 2) {
        blendId = constants.getParamValueString(DISTORTION_2_BLEND_ID, "ID");
    }
    
    juce::String volumeId = constants.getParamValueString(DISTORTION_1_VOLUME_ID, "ID");
    if(indexParam == 2) {
        volumeId = constants.getParamValueString(DISTORTION_2_VOLUME_ID, "ID");
    }
    
    juce::String switchId = constants.getParamValueString(DISTORTION_1_SWITCH_ID, "ID");
    if(indexParam == 2) {
        switchId = constants.getParamValueString(DISTORTION_2_SWITCH_ID, "ID");
    }

    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, driveId, driveSlider);
    
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    driveSlider.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    driveSlider.setRange(driveMin, driveMax);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    driveSlider.addListener(this);
    driveSlider.setTextBoxIsEditable(true);
    
    
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.setFont(FONT_SIZE_1);
    //driveLabel.attachToComponent (&driveSlider, false);
    
    driveLabel.setBounds(62, 20, 50, 100);
    driveLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (driveLabel);
    
    rangeLabel.setText ("Blend", juce::dontSendNotification);
    rangeLabel.setFont(FONT_SIZE_1);
    rangeLabel.setBounds(138, 20, 50, 100);
    rangeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (rangeLabel);
    
    addAndMakeVisible(&driveSlider);
    
    
    
    //frequencySlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    
    rangeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, rangeId, rangeSlider);
    
    rangeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rangeSlider.setRange(constants.getParamValue(DISTORTION_1_RANGE_ID, "MIN"), constants.getParamValue(DISTORTION_1_RANGE_ID, "MAX"));
    rangeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    rangeSlider.addListener(this);
    //addAndMakeVisible(&rangeSlider);
    
    blendSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, blendId, blendSlider);
    
    blendSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    blendSlider.setRange(constants.getParamValue(DISTORTION_1_BLEND_ID, "MIN"), constants.getParamValue(DISTORTION_1_BLEND_ID, "MAX"));
    blendSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    blendSlider.addListener(this);
    blendSlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&blendSlider);
    
    /*
    volumeSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, volumeId, volumeSlider);
    
    volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    volumeSlider.setRange(VOLUME_MIN, VOLUME_MAX);
    volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 30);
    volumeSlider.addListener(this);
    addAndMakeVisible(&volumeSlider);*/
    
    switchButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, switchId, switchButton);
    
    //switchButton.setRange(VOLUME_MIN, VOLUME_MAX);
    //switchButton.setButtonText(<#const String &newText#>)(Slider::TextBoxBelow, true, 100, 30);
    switchButton.addListener(this);
    addAndMakeVisible(&switchButton);
    
    setSize(300, 400);
}

Distortion::~Distortion()
{
}

void Distortion::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setFont (FONT_SIZE_1);
    g.drawText ("Distortion", getLocalBounds().reduced(10),
                juce::Justification::topLeft, true);   // draw some placeholder text
    
    //https://www.w3schools.com/colors/colors_rgb.asp
    //std::cout << "Index param " << index << std::endl;
    
    juce::Colour disabledColour = constants.getRotarySliderDisabledColour();
    juce::Colour enabledColour = constants.getRotarySliderEnabledColour();
    juce::Colour rotarySliderFillDarkColour = constants.getRotarySliderFillDarkColour();
    
    if(switchButton.getToggleState() == 0) {
        driveSlider.setColour(juce::Slider::rotarySliderFillColourId, disabledColour);
        driveSlider.setColour(juce::Slider::thumbColourId, disabledColour);
        
        rangeSlider.setColour(juce::Slider::rotarySliderFillColourId, disabledColour);
        rangeSlider.setColour(juce::Slider::thumbColourId, disabledColour);
        
        blendSlider.setColour(juce::Slider::rotarySliderFillColourId, disabledColour);
        blendSlider.setColour(juce::Slider::thumbColourId, disabledColour);
        
        //volumeSlider.setColour(Slider::rotarySliderFillColourId, disabledColour);
        //volumeSlider.setColour(Slider::thumbColourId, disabledColour);
        
        driveSlider.setEnabled(false);
        rangeSlider.setEnabled(false);
        blendSlider.setEnabled(false);
        //volumeSlider.setEnabled(false);
        
        return;
    }
    
    blendSlider.setColour(juce::Slider::rotarySliderFillColourId, rotarySliderFillDarkColour);
    blendSlider.setColour(juce::Slider::thumbColourId, enabledColour);
    
    driveSlider.setEnabled(true);
    rangeSlider.setEnabled(true);
    blendSlider.setEnabled(true);
    //volumeSlider.setEnabled(true);
    
    int colours[8][3];
    
    colours[0][0] = COLOUR_GREEN_1;
    colours[0][1] = COLOUR_GREEN_2;
    colours[0][2] = COLOUR_GREEN_3;
    
    colours[1][0] = COLOUR_GREEN_1;
    colours[1][1] = COLOUR_GREEN_2;
    colours[1][2] = COLOUR_GREEN_3;
    
    colours[2][0] = COLOUR_YELLOW_1;
    colours[2][1] = COLOUR_YELLOW_2;
    colours[2][2] = COLOUR_YELLOW_3;
    
    colours[3][0] = COLOUR_YELLOW_1;
    colours[3][1] = COLOUR_YELLOW_2;
    colours[3][2] = COLOUR_YELLOW_3;
    
    colours[4][0] = COLOUR_ORANGE_1;
    colours[4][1] = COLOUR_ORANGE_2;
    colours[4][2] = COLOUR_ORANGE_3;
    
    colours[5][0] = COLOUR_ORANGE_1;
    colours[5][1] = COLOUR_ORANGE_2;
    colours[5][2] = COLOUR_ORANGE_3;
    
    colours[6][0] = COLOUR_RED_1;
    colours[6][1] = COLOUR_RED_2;
    colours[6][2] = COLOUR_RED_3;
    
    colours[7][0] = COLOUR_BLACK_1;
    colours[7][1] = COLOUR_BLACK_2;
    colours[7][2] = COLOUR_BLACK_3;
    
    colourDriveSlider = utilities.renderColor(driveSlider.getValue(), constants.getParamValue(DISTORTION_1_DRIVE_ID, "MIN"), constants.getParamValue(DISTORTION_1_DRIVE_ID, "MAX"), colours);
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, colourDriveSlider);
    driveSlider.setColour(juce::Slider::thumbColourId, colourDriveSlider); //pallina
    
    /*
    colourRangeSlider = utilities.renderColor(rangeSlider.getValue(), RANGE_MIN, RANGE_MAX, colours);
    rangeSlider.setColour(Slider::rotarySliderFillColourId, colourRangeSlider);
    rangeSlider.setColour(Slider::thumbColourId, colourRangeSlider);*/
    
    /*
    colourBlendSlider = utilities.renderColor(blendSlider.getValue(), BLEND_MIN, BLEND_MAX, colours);
    blendSlider.setColour(Slider::rotarySliderFillColourId, colourBlendSlider);
    blendSlider.setColour(Slider::thumbColourId, colourBlendSlider);*/
    
    //colourVolumeSlider = utilities.renderColor(volumeSlider.getValue(), VOLUME_MIN, VOLUME_MAX);
    //volumeSlider.setColour(Slider::rotarySliderFillColourId, colourVolumeSlider);
    //volumeSlider.setColour(Slider::thumbColourId, colourVolumeSlider);
    
    //driveSlider.getLookAndFeel().drawRotarySlider(g, 0, 0, 20, 20, 10, 0, 100, driveSlider);
    
    //driveSlider.setLookAndFeel(<#LookAndFeel *newLookAndFeel#>)
}

void Distortion::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(10, 20);
    switchButton.setBounds(area.removeFromLeft(30).removeFromTop(30));
    
    //LookAndFeel_V1;
    
    juce::Rectangle<int> area2 = getLocalBounds();
    area2.setPosition(50, 20);
    driveSlider.setBounds(area2.removeFromLeft(75).removeFromTop(130));
    //rangeSlider.setBounds(area2.removeFromLeft(50).removeFromTop(200));
    blendSlider.setBounds(area2.removeFromLeft(75).removeFromTop(130));
    //volumeSlider.setBounds(area2.removeFromLeft(50).removeFromTop(200));
    
    
    
}

void Distortion::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &driveSlider)
    {
        std::atomic<float>* driveParameter = processor.drive1Parameter;
        
        if(index == 2) {
            driveParameter = processor.drive2Parameter;
        }
        
        std::cout << "DRIVE " << index << driveSlider.getValue() << std::endl;
        driveParameter = new std::atomic<float>(driveSlider.getValue());
        
        //repaint();
        
        //switchButton.repaint();
    }
    
    if(slider == &rangeSlider)
    {
        std::atomic<float>* rangeParameter = processor.range1Parameter;
        
        if(index == 2) {
            rangeParameter = processor.range2Parameter;
        }
        
        rangeParameter = new std::atomic<float>(rangeSlider.getValue());
    }
    
    if(slider == &blendSlider)
    {
        std::atomic<float>* blendParameter = processor.blend1Parameter;
        
        if(index == 2) {
            blendParameter = processor.blend2Parameter;
        }
        
        std::cout << "BLEND " << index << blendSlider.getValue() << std::endl;
        blendParameter = new std::atomic<float>(blendSlider.getValue());
    }
    
    /*
    if(slider == &volumeSlider)
    {
        std::atomic<float>* volumeParameter = processor.volume1Parameter;
        
        if(index == 2) {
            volumeParameter = processor.volume2Parameter;
        }
        
        std::cout << "VOLUME " << index << volumeSlider.getValue() << std::endl;
        volumeParameter = new std::atomic<float>(volumeSlider.getValue());
    }*/
}

void Distortion::buttonClicked(juce::Button* button)
{
    if(button == &switchButton)
    {
        std::atomic<bool>* switchParameter = processor.distortion1SwitchParameter;
        
        if(index == 2) {
            switchParameter = processor.distortion2SwitchParameter;
        }
        
        std::cout << "SWITCH " << index << " " << switchButton.getToggleState() << std::endl;
        switchParameter = new std::atomic<bool>(switchButton.getToggleState());
        
        repaint();
    }
}

