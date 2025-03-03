/*
  ==============================================================================

    Oscillator.cpp
    Created: 4 Jan 2025 3:03:39pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(S1AudioProcessor& p, int indexParam) :
processor(p)
{
    setSize(250, 150);
    
    index = indexParam;
    
    juce::String waveTypeId = constants.getParamValueString(WAVE_TYPE_1_ID, "ID");
    juce::String levelId = constants.getParamValueString(LEVEL_1_ID, "ID");
    float levelMin = constants.getParamValue(LEVEL_1_ID, "MIN");
    float levelMax = constants.getParamValue(LEVEL_1_ID, "MAX");
    juce::String volumeLabelName = VOLUME_LABEL_1;
    if(index == 2) {
        waveTypeId = constants.getParamValueString(WAVE_TYPE_2_ID, "ID");
        levelId = constants.getParamValueString(LEVEL_2_ID, "ID");
        levelMin = constants.getParamValue(LEVEL_2_ID, "MIN");
        levelMax = constants.getParamValue(LEVEL_2_ID, "MAX");
        volumeLabelName = VOLUME_LABEL_2;
    }
    
    volumeLabel.setName(volumeLabelName);
    volumeLabel.setText ("Volume", juce::dontSendNotification);
    volumeLabel.setFont(FONT_SIZE_1);
    volumeLabel.setBounds(145, 35, 50, 100);
    volumeLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible (volumeLabel);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.addItem("Triangle", 4);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    oscMenu.setJustificationType(juce::Justification::centred);
    
    
        
    
    waveTypeComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState, waveTypeId, oscMenu);
    
    auto waveType1Parameter = processor.treeState.getRawParameterValue(waveTypeId);
    //std::cout << "xxxxxx " << float(*waveType1Parameter) << std::endl
    
    currentWaveType = float(*waveType1Parameter);
    
    
    /*
    ImageButton myImageButton;
    Image normalButton = ImageCache::getFromMemory (BinaryData::knob_silver_png, BinaryData::knob_silver_pngSize);
    Image overButton = ImageCache::getFromMemory (BinaryData::knob_silver_png, BinaryData::knob_silver_pngSize);
    Image downButton = ImageCache::getFromMemory (BinaryData::knob_silver_png, BinaryData::knob_silver_pngSize);
    button1.setImages (false, false, true, normalButton, 1.0f, {}, overButton, 1.0f, {}, downButton, 1.0f, {});
     */
    
    addAndMakeVisible(button1);
    //button1.setLookAndFeel(&imageButton1);
    button1.setSize(150, 150);
    button1.setInterceptsMouseClicks(true, true);
    
    button1.addListener(this);
    
    button1.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
    button1.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    //button1.setRange(LEVEL2_MIN, LEVEL2_MAX);
    //level2Slider.setValue(processor.ampLeadMidKnobState);
    /*button1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    button1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    button1.setNumDecimalPlacesToDisplay(1);
    button1.setDoubleClickReturnValue(true, 0.0);*/
    
    levelSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, levelId, levelSlider);
    
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    levelSlider.setRange(levelMin, levelMax);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);
    levelSlider.setTextBoxIsEditable(true);
    levelSlider.setSkewFactorFromMidPoint ((levelMax - levelMin) / 1.5);
    
    addAndMakeVisible(&levelSlider);
    levelSlider.addListener(this);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
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
    g.drawText ("Oscillator Pysto", getLocalBounds().reduced(10),
                juce::Justification::topLeft, true);   // draw some placeholder text
    
    //oscillatorImage = ImageCache::getFromMemory (BinaryData::square3_png, BinaryData::square3_pngSize);
    
    
    //if(currentWaveType > 2) {
        //oscillatorImage = ImageCache::getFromMemory (BinaryData::knob_silver_png, BinaryData::knob_silver_pngSize);
    //}
    
    /*
    ImageComponent* imgc = new ImageComponent();
    imgc->setImage(oscillatorImage);
    imgc->setSize(200, 200);
    imgc->setBoundsToFit(imgc->getScreenBounds(), Justification::centredRight, true);
    
    imgc->setBounds(0, 0, 200, 200);*/
    
    //g.drawImage(oscillatorImage, 0, 0, 200, 200, 0, 0, 200, 200);
    
    
    juce::Path path;/*
    path.startNewSubPath (juce::Point<float> (10, 10));
    path.lineTo (juce::Point<float> (20, 10));
    path.lineTo (juce::Point<float> (20, 20));
    path.lineTo (juce::Point<float> (10, 20));
    path.closeSubPath();*/
    
    
    g.setColour (juce::Colours::orange);
    
    float overlays[20][2];
    
    overlays[0][0] = 0.5f;
    overlays[0][1] = 1.0f;
    
    overlays[1][0] = 2.0f;
    overlays[1][1] = 0.5f;
    
    overlays[2][0] = 4.0f;
    overlays[2][1] = 0.3f;
    
    overlays[3][0] = 6.0f;
    overlays[3][1] = 0.1f;
    
    g.setColour (juce::Colours::yellow);
    juce::Line<float> horizontalLine (juce::Point<float> (OSC_PADDING - 10, OSC_PADDING + (OSC_HEIGHT / 2)), juce::Point<float> (OSC_WIDTH + OSC_PADDING + 10, OSC_PADDING + (OSC_HEIGHT / 2)));
    g.drawLine (horizontalLine, 0.2);
    
    if(currentWaveType == 0) {
        float x = 0;
        float y = OSC_HEIGHT / 2;
        float stepsNumber = 100;
        float xSpace = OSC_WIDTH / stepsNumber;
        for(int i = 1; i <= stepsNumber; i++) {
            float newX = 2.0 * juce::MathConstants<double>::pi * i / stepsNumber;
            float newY = (-(OSC_HEIGHT / 2) * sin(newX)) + (OSC_HEIGHT / 2);
            newX = xSpace * i;
            juce::Line<float> line (juce::Point<float> (x + OSC_PADDING, y + OSC_PADDING), juce::Point<float> (newX + OSC_PADDING, newY + OSC_PADDING));
            
            utilities.drawBlur(g, line, juce::Colours::orange, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    if(currentWaveType == 1) {
        float x = 0;
        float y = OSC_HEIGHT / 2;
        float stepsNumber = OSC_WIDTH;
        float xSpace = OSC_WIDTH / stepsNumber;
        float ySpace = OSC_HEIGHT / stepsNumber;
        for(int i = 1; i <= stepsNumber; i++) {
            float newX = xSpace * i;
            float newY = (-ySpace * (i + (OSC_WIDTH / 2))) + (OSC_HEIGHT);
            if(newY < 0) {
                newY = OSC_HEIGHT + newY;
            }
            
            juce::Line<float> line (juce::Point<float> (x + OSC_PADDING, y + OSC_PADDING), juce::Point<float> (newX + OSC_PADDING, newY + OSC_PADDING));
            
            utilities.drawBlur(g, line, juce::Colours::orange, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    if(currentWaveType == 2) {
        float x = 0;
        float y = 0;
        float stepsNumber = OSC_WIDTH;
        float xSpace = OSC_WIDTH / stepsNumber;
        for(int i = 1; i <= stepsNumber; i++) {
            float newX = xSpace * i;
            float newY = 0;
            if(newX > (OSC_WIDTH / 2)) {
                newY = OSC_HEIGHT;
            }
            
            juce::Line<float> line (juce::Point<float> (x + OSC_PADDING, y + OSC_PADDING), juce::Point<float> (newX + OSC_PADDING, newY + OSC_PADDING));
            
            utilities.drawBlur(g, line, juce::Colours::orange, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    if(currentWaveType == 3) {
        float x = 0;
        float y = OSC_HEIGHT / 2;
        float stepsNumber = OSC_WIDTH;
        float xSpace = OSC_WIDTH / stepsNumber;
        float ySpace = (OSC_HEIGHT * 2) / stepsNumber;
        int factor = -1;
        for(int i = 1; i <= stepsNumber; i++) {
            float newX = xSpace * i;
            float newY = y + (ySpace * factor);
            if(newY < 0) {
                factor = 1;
                float diff = 0 - newY;
                newY = 0 + diff;
            }
            if(newY > OSC_HEIGHT) {
                factor = -1;
                float diff = newY - OSC_HEIGHT;
                newY = OSC_HEIGHT - diff;
            }
            
            juce::Line<float> line (juce::Point<float> (x + OSC_PADDING, y + OSC_PADDING), juce::Point<float> (newX + OSC_PADDING, newY + OSC_PADDING));
            
            /*
            g.drawLine (line, 0.5f);
            g.setOpacity(0.5);
            g.drawLine (line, 2.0f);
            g.setOpacity(0.2);
            g.drawLine (line, 5.0f);
            g.setOpacity(0.1);
            g.drawLine (line, 7.0f);
            g.setOpacity(1);
            */
            
            utilities.drawBlur(g, line, juce::Colours::orange, overlays);
            
            x = newX;
            y = newY;
        }
    }
    
    /*
    DropShadow ds;
    ds.radius = 5;
    //ds.offset(juce::Point<float> (0, 0));
    ds.drawForPath(g, path);*/
}

void Oscillator::resized()
{
    const int oscWidth = 0;
    const int oscHeight = 0;
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(oscWidth).removeFromLeft(oscHeight));
    
    juce::Rectangle<int> area2 = getLocalBounds().removeFromRight(100);
    levelSlider.setBounds(area2.removeFromLeft(100).removeFromTop(150));
    
}

void Oscillator::comboBoxChanged (juce::ComboBox* box)
{
    if(box == &oscMenu)
    {
        processor.waveType1Parameter = new std::atomic<float>(oscMenu.getSelectedIdAsValue().getValue());
    }
}


void Oscillator::buttonClicked (juce::Button* button)
{
    if(button == &button1)
    {
        currentWaveType = (currentWaveType+1) % OSC_QTY;
        oscMenu.setSelectedId(currentWaveType + 1);
        this->repaint();
    }
    
    
}

void Oscillator::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &levelSlider)
    {
        std::atomic<float>* levelParameter = processor.level1Parameter;
        
        if(index == 2) {
            levelParameter = processor.level2Parameter;
        }
        
        levelParameter = new std::atomic<float>(levelSlider.getValue());
    }
}
