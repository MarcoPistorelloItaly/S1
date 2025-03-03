/*
  ==============================================================================

    Filter.cpp
    Created: 4 Jan 2025 3:14:04pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"
#include "PluginProcessor.h"

//==============================================================================
Filter::Filter(S1AudioProcessor& p, int indexParam) :
processor(p)
{
    index = indexParam;
    
    juce::String filterCutoffDialId = constants.getParamValueString(FILTER_1_CUTOFF_ID, "ID");
    if(indexParam == 2) {
        filterCutoffDialId = constants.getParamValueString(FILTER_2_CUTOFF_ID, "ID");
    }
    
    juce::String filterResDialId = constants.getParamValueString(FILTER_1_RES_ID, "ID");
    if(indexParam == 2) {
        filterResDialId = constants.getParamValueString(FILTER_2_RES_ID, "ID");
    }
    
    juce::String filterMenuId = constants.getParamValueString(FILTER_1_TYPE_ID, "ID");
    if(indexParam == 2) {
        filterMenuId = constants.getParamValueString(FILTER_2_TYPE_ID, "ID");
    }
    
    juce::String filterAttackId = constants.getParamValueString(FILTER_1_ATTACK_ID, "ID");
    if(indexParam == 2) {
        filterAttackId = constants.getParamValueString(FILTER_2_ATTACK_ID, "ID");
    }
    
    juce::String switchId = constants.getParamValueString(FILTER_1_SWITCH_ID, "ID");
    if(indexParam == 2) {
        switchId = constants.getParamValueString(FILTER_2_SWITCH_ID, "ID");
    }
    
    float filterCutoffMin = constants.getParamValue(FILTER_1_CUTOFF_ID, "MIN");
    float filterCutoffMax = constants.getParamValue(FILTER_1_CUTOFF_ID, "MAX");
    float filterCutoffDefault = constants.getParamValue(FILTER_1_CUTOFF_ID, "DEFAULT");
    
    float filterResMin = constants.getParamValue(FILTER_1_RES_ID, "MIN");
    float filterResMax = constants.getParamValue(FILTER_1_RES_ID, "MAX");
    float filterResDefault = constants.getParamValue(FILTER_1_RES_ID, "DEFAULT");
    
    float filterAttackMin = constants.getParamValue(FILTER_1_ATTACK_ID, "MIN");
    float filterAttackMax = constants.getParamValue(FILTER_1_ATTACK_ID, "MAX");
    float filterAttackDefault = constants.getParamValue(FILTER_1_ATTACK_ID, "DEFAULT");

    filterCutoffDialAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, filterCutoffDialId, filterCutoffDialSlider);
    
    filterCutOffLabel.setText ("Cut\nOff", juce::dontSendNotification);
    filterCutOffLabel.setFont(FONT_SIZE_1);
    filterCutOffLabel.setBounds(150, 20, 50, 100);
    filterCutOffLabel.setJustificationType(juce::Justification::verticallyCentred);
    addAndMakeVisible (filterCutOffLabel);
    
    filterResLabel.setText ("Res", juce::dontSendNotification);
    filterResLabel.setFont(FONT_SIZE_1);
    filterResLabel.setBounds(240, 20, 50, 100);
    filterResLabel.setJustificationType(juce::Justification::verticallyCentred);
    addAndMakeVisible (filterResLabel);
    
    filterAttackLabel.setText ("Attack", juce::dontSendNotification);
    filterAttackLabel.setFont(FONT_SIZE_1);
    filterAttackLabel.setBounds(315, 20, 50, 100);
    filterAttackLabel.setJustificationType(juce::Justification::verticallyCentred);
    addAndMakeVisible (filterAttackLabel);
    
    filterCutoffDialSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterCutoffDialSlider.setRange(filterCutoffMin, filterCutoffMax);
    filterCutoffDialSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    filterCutoffDialSlider.addListener(this);
    filterCutoffDialSlider.setTextValueSuffix("Hz");
    filterCutoffDialSlider.setTextBoxIsEditable(true);
    filterCutoffDialSlider.setSkewFactor(0.5, false);
    addAndMakeVisible(&filterCutoffDialSlider);
    
    filterResDialAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, filterResDialId, filterResDialSlider);
    
    filterResDialSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterResDialSlider.setRange(filterResMin, filterResMax);
    filterResDialSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    filterResDialSlider.addListener(this);
    filterResDialSlider.setTextBoxIsEditable(true);
    addAndMakeVisible(&filterResDialSlider);
    
    filterResDialAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, filterResDialId, filterResDialSlider);
    
    filterMenu.setJustificationType(juce::Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("Band Pass", 2);
    filterMenu.addItem("High Pass", 3);
    //addAndMakeVisible(&filterMenu);
    
    filterMenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState, filterMenuId, filterMenu);
    
    filterAttackDialSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterAttackDialSlider.setRange(filterAttackMin, filterAttackMax);
    filterAttackDialSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    filterAttackDialSlider.addListener(this);
    filterAttackDialSlider.setTextBoxIsEditable(true);
    filterAttackDialSlider.setTextValueSuffix("s");
    addAndMakeVisible(&filterAttackDialSlider);
    
    filterAttackDialAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, filterAttackId, filterAttackDialSlider);
    
    addAndMakeVisible(filterTypeButton);
    filterTypeButton.setSize(150, 150);
    filterTypeButton.setInterceptsMouseClicks(true, true);
    filterTypeButton.addListener(this);
    filterTypeButton.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    filterTypeButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    
    switchButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, switchId, switchButton);
    
    //switchButton.setRange(VOLUME_MIN, VOLUME_MAX);
    //switchButton.setButtonText(<#const String &newText#>)(Slider::TextBoxBelow, true, 100, 30);
    switchButton.addListener(this);
    addAndMakeVisible(&switchButton);
    
    
    
    filterMenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState, filterMenuId, filterMenu);
    
    auto filterType1Parameter = processor.treeState.getRawParameterValue(filterMenuId);
    
    currentFilterType = float(*filterType1Parameter);
    
    setSize(500, 150);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
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
    g.drawText ("Filter", getLocalBounds().reduced(10),
                juce::Justification::topLeft, true);   // draw some placeholder text
    
    juce::Colour graphicsSlider = juce::Colours::orange;
    
    juce::Colour rotarySliderDisabledColour = constants.getRotarySliderDisabledColour();
    juce::Colour rotarySliderEnabledColour = constants.getRotarySliderEnabledColour();
    juce::Colour rotarySliderFillDarkColour = constants.getRotarySliderFillDarkColour();
    
    juce::Colour sliderColour = rotarySliderEnabledColour;
    juce::Colour sliderFillColour = rotarySliderFillDarkColour;
    juce::Colour red = constants.getRotarySliderFillRed();
    
    bool sliderStatus = true;
    
    if(switchButton.getToggleState() == 0) {
        sliderColour = rotarySliderDisabledColour;
        sliderStatus = false;
        graphicsSlider = juce::Colours::lightgrey;
        sliderFillColour = rotarySliderDisabledColour;
    }
    
    filterCutoffDialSlider.setEnabled(sliderStatus);
    filterResDialSlider.setEnabled(sliderStatus);
    filterAttackDialSlider.setEnabled(sliderStatus);
    
    //filterCutoffDialSlider.setColour(Slider::trackColourId, sliderFillColour);
    filterCutoffDialSlider.setColour(juce::Slider::thumbColourId, sliderColour);
    
    //filterResDialSlider.setColour(Slider::trackColourId, sliderFillColour);
    filterResDialSlider.setColour(juce::Slider::thumbColourId, sliderColour);
    
    //filterAttackDialSlider.setColour(Slider::rotarySliderFillColourId, sliderFillColour);
    filterAttackDialSlider.setColour(juce::Slider::thumbColourId, sliderColour);
    
    float overlays[20][2];
    
    overlays[0][0] = 0.5f;
    overlays[0][1] = 1.0f;
    
    overlays[1][0] = 2.0f;
    overlays[1][1] = 0.5f;
    
    overlays[2][0] = 4.0f;
    overlays[2][1] = 0.3f;
    
    if(currentFilterType == 0) {
        float x = 0;
        float y = 0;
        
        for(int i = 1; i <= FILTER_WIDTH; i++) {
            float xInput = ((float(i) / FILTER_WIDTH) * 24) - 12;
            //std::cout << "xInput  -  " << xInput << std::endl;
            float newX = i;
            float newY = (((2.f / juce::float_Pi) * atan(xInput) * FILTER_HEIGHT) / 2) + (FILTER_HEIGHT / 2);
            
            if(i == 1) {
                y = newY;
            }
            
            newX = i;
            juce::Line<float> line (juce::Point<float> (x + FILTER_PADDING, y + FILTER_PADDING), juce::Point<float> (newX + FILTER_PADDING, newY + FILTER_PADDING));
            
            utilities.drawBlur(g, line, graphicsSlider, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    if(currentFilterType == 1) {
        float x = FILTER_WIDTH;
        float y = 0;
        
        for(int i = 1; i <= FILTER_WIDTH; i++) {
            float xInput = ((float(i) / FILTER_WIDTH) * 24) - 12;
            //std::cout << "xInput  -  " << xInput << std::endl;
            float newX = FILTER_WIDTH - i;
            float newY = (((2.f / juce::float_Pi) * atan(xInput) * FILTER_HEIGHT) / 2) + (FILTER_HEIGHT / 2);
            
            if(i == 1) {
                y = newY;
            }
            
            newX = FILTER_WIDTH - i;
            juce::Line<float> line (juce::Point<float> (x + FILTER_PADDING, y + FILTER_PADDING), juce::Point<float> (newX + FILTER_PADDING, newY + FILTER_PADDING));
            
            utilities.drawBlur(g, line, graphicsSlider, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    if(currentFilterType == 2) {
        float x = 0;
        float y = FILTER_HEIGHT;
        float stepsNumber = 100;
        float xSpace = FILTER_WIDTH / stepsNumber;
        for(int i = 1; i <= stepsNumber; i++) {
            float newX = (2.0 * juce::MathConstants<double>::pi * i / stepsNumber) - (juce::MathConstants<double>::pi / 2);
            float newY = (-(FILTER_HEIGHT / 2) * sin(newX)) + (FILTER_HEIGHT / 2);
            newX = xSpace * i;
            juce::Line<float> line (juce::Point<float> (x + FILTER_PADDING, y + FILTER_PADDING), juce::Point<float> (newX + FILTER_PADDING, newY + FILTER_PADDING));
            
            utilities.drawBlur(g, line, graphicsSlider, overlays);
            
            x = newX;
            y = newY;
        }
    }
}

void Filter::resized()
{
    
    juce::Rectangle<int> area = getLocalBounds().reduced(10, 20);
    switchButton.setBounds(area.removeFromLeft(30).removeFromTop(30));
    
    juce::Rectangle<int> area2 = getLocalBounds();
    
    area2.setPosition(150, 0);
    
    filterCutoffDialSlider.setBounds(area2.removeFromLeft(100).removeFromTop(200));
    filterResDialSlider.setBounds(area2.removeFromLeft(50).removeFromTop(200));
    
    juce::Rectangle<int> area3 = getLocalBounds();
    area3.setPosition(300, 15);
    filterAttackDialSlider.setBounds(area3.removeFromLeft(75).removeFromTop(135));
    //filterMenu.setBounds(area2.removeFromLeft(50).removeFromTop(200));
}

void Filter::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &filterCutoffDialSlider)
    {
        std::atomic<float>* filterCutoffDialParameter = processor.filterCutoffDial1Parameter;
        
        if(index == 2) {
            filterCutoffDialParameter = processor.filterCutoffDial2Parameter;
        }
        
        //std::cout << "FilterCutoffDialSlider " << index << filterCutoffDialSlider.getValue() << std::endl;
        filterCutoffDialParameter = new std::atomic<float>(filterCutoffDialSlider.getValue());
    }
    
    if(slider == &filterResDialSlider)
    {
        std::atomic<float>* filterResDialParameter = processor.filterResDial1Parameter;
        
        if(index == 2) {
            filterResDialParameter = processor.filterResDial2Parameter;
        }
        
//        std::cout << "FilterResDialSlider " << index << filterResDialSlider.getValue() << std::endl;
        filterResDialParameter = new std::atomic<float>(filterResDialSlider.getValue());
    }
    
    if(slider == &filterAttackDialSlider)
    {
        std::atomic<float>* filterAttackDialParameter = processor.filterAttack1Parameter;
        
        if(index == 2) {
            filterAttackDialParameter = processor.filterAttack2Parameter;
        }
        
        //std::cout << "FilterAttackDialSlider " << index << filterAttackDialSlider.getValue() << std::endl;
        filterAttackDialParameter = new std::atomic<float>(filterAttackDialSlider.getValue());
    }

}

void Filter::comboBoxChanged (juce::ComboBox* box)
{
    if(box == &filterMenu)
    {
        std::atomic<float>* filterMenuParameter = processor.filterMenu1Parameter;
        
        if(index == 2) {
            filterMenuParameter = processor.filterMenu2Parameter;
        }
        
        filterMenuParameter = new std::atomic<float>(filterMenu.getSelectedIdAsValue().getValue());
    }
}

void Filter::buttonClicked(juce::Button* button)
{
    if(button == &switchButton)
    {
        std::atomic<float>* switchParameter = processor.filter1SwitchParameter;
        
        if(index == 2) {
            switchParameter = processor.filter2SwitchParameter;
        }
        
        switchParameter = new std::atomic<float>(switchButton.getToggleState());
        
        repaint();
    }
    
    if(button == &filterTypeButton)
    {
        if(switchButton.getToggleState() == 1) {
            currentFilterType = (currentFilterType+1) % FILTER_QTY;
            filterMenu.setSelectedId(currentFilterType + 1);
        }
    }
}
