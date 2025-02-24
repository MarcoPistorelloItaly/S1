/*
  ==============================================================================

    ProgramSelector.h
    Created: 31 Dec 2024 11:35:58am
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utilities.h"

#define SELECTED_PROGRAM_PARAMETER_ID "SelectedProgramParameter"
#define SELECTED_PROGRAM_PARAMETER_NAME "Selected Program"

//https://docs.juce.com/master/classMenuBarComponent.html#details
//https://docs.juce.com/master/classListBox.html#details

//==============================================================================
/*
*/
class ProgramSelector    : public juce::Component, public juce::Button::Listener
{
public:
    ProgramSelector(S1AudioProcessor& p);
    ~ProgramSelector();

    void paint (juce::Graphics&) override;
    
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    
    void changeProgramSelectorName(std::string);
    
    void setPresetsBrowserShown(int);
    
    void setPresetSaveShown(int);
    

private:
    S1AudioProcessor& processor;
    juce::ArrowButton prevButton;
    juce::ArrowButton nextButton;
    juce::Label currentProgramName;
    Utilities utilities;
    
    juce::TextButton browseButton;
    juce::TextButton saveButton;
    
    int presetsBrowserShown = 0;
    int presetSaveShown = 0;
    
    //AudioParameterFloat* gain;
    //AudioParameterChoice*  choices;

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> currentProgramAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgramSelector)
};
