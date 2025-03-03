/*
  ==============================================================================

    ProgramSelector.cpp
    Created: 31 Dec 2024 11:35:58am
    Author:  Marco

  ==============================================================================
*/

#include "ProgramSelector.h"

#include <JuceHeader.h>
#include "PluginEditor.h"
#include "Constants.h"

//==============================================================================
ProgramSelector::ProgramSelector(S1AudioProcessor& p) :
processor(p), prevButton("Prev Button", 0.5, juce::Colours::black), nextButton("Next Button", 100, juce::Colours::black)
{
    prevButton.addListener(this);
    prevButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(prevButton);
    
    nextButton.addListener(this);
    nextButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(nextButton);
    
    browseButton.addListener(this);
    browseButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    browseButton.setButtonText("BROWSE");
    addAndMakeVisible(browseButton);
    
    saveButton.addListener(this);
    saveButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    saveButton.setButtonText("SAVE");
    addAndMakeVisible(saveButton);
    
    setSize(1100, PROGRAM_SELECTOR_HEIGHT);
    
    std::string currentPresetComposedName = processor.getCurrentPresetComposedName();
    
    juce::String x = utilities.buildPatchNameFromString(currentPresetComposedName);
    
    //currentProgramName.setText(utilities.buildPatchNameFromString(currentPresetComposedName),
                              //juce::NotificationType::sendNotification);
}

ProgramSelector::~ProgramSelector()
{
}

void ProgramSelector::paint (juce::Graphics& g)
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
    
    //TODO: Try to find the initial preset name
    //changeProgramSelectorName("ciaociao");
    g.drawText (juce::String(currentProgramName.getText()), getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ProgramSelector::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(10);
    area.setLeft(10);
    browseButton.setBounds(area.removeFromLeft(50).removeFromTop(PROGRAM_SELECTOR_HEIGHT));
    
    juce::Rectangle<int> area1 = getLocalBounds().reduced(10);
    area1.setLeft(70);
    saveButton.setBounds(area1.removeFromLeft(50).removeFromTop(PROGRAM_SELECTOR_HEIGHT));
    
    juce::Rectangle<int> area2 = getLocalBounds().reduced(10);
    area2.setLeft(200);
    prevButton.setBounds(area2.removeFromLeft(50).removeFromTop(PROGRAM_SELECTOR_HEIGHT));
    
    juce::Rectangle<int> area3 = getLocalBounds().reduced(10);
    area3.setLeft(850);
    nextButton.setBounds(area3.removeFromLeft(50).removeFromTop(PROGRAM_SELECTOR_HEIGHT));
}

void ProgramSelector::buttonClicked(juce::Button* button)
{
    std::string currentPresetComposedName = "";
    if(button == &prevButton)
    {
        currentPresetComposedName = processor.movePresets(-1);
    }
    
    if(button == &nextButton)
    {
        currentPresetComposedName = processor.movePresets(1);
    }
    
    if(button == &browseButton)
    {
        if(presetsBrowserShown == 0) {
            processor.showPresetsBrowser();
            //presetsBrowserShown = 1;
            return;
        }
        if(presetsBrowserShown == 1) {
            processor.hidePresetsBrowser();
            //presetsBrowserShown = 0;
            return;
        }
    }
    
    if(button == &saveButton)
    {
        if(presetSaveShown == 0) {
            processor.showPresetSave();
            return;
        }
        if(presetSaveShown == 1) {
            processor.hidePresetSave();
            return;
        }
    }
    
    //TODO: Use the following changeProgramSelectorName function
    currentProgramName.setText(utilities.buildPatchNameFromString(currentPresetComposedName),
                               juce::NotificationType::sendNotification);
    
    repaint();
}

void ProgramSelector::changeProgramSelectorName(std::string newPresetName) {
    juce::String xxx = utilities.buildPatchNameFromString(newPresetName);
    currentProgramName.setText(utilities.buildPatchNameFromString(newPresetName), juce::NotificationType::sendNotification);
    
    repaint();
}

void ProgramSelector::setPresetsBrowserShown(int newStatus) {
    presetsBrowserShown = newStatus;
}

void ProgramSelector::setPresetSaveShown(int newStatus) {
    presetSaveShown = newStatus;
}
