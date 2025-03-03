/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PresetsBrowser.h"
#include "PresetsSave.h"
#include "ProgramSelector.h"
#include "SynthEngine.h"

//==============================================================================
/**
*/
class S1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    S1AudioProcessorEditor (S1AudioProcessor&);
    ~S1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    ProgramSelector& getProgramSelector();
    
    void showPresetsBrowser();
    void hidePresetsBrowser();
    
    void showPresetSave();
    void hidePresetSave();
    
    void selectPresetFolder(std::string folderName);
    void selectSavePresetFolder(std::string folderName);
    void changeProgramSelectorName(std::string);
    
    void refreshFoldersAndPresets();
    
    void resetLayers();
    void aaa();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    S1AudioProcessor& audioProcessor;
    
    PresetSave presetSave;
    
    PresetsBrowser presetsBrowser;
    
    ProgramSelector programSelector;
    
    SynthEngine synthEngine1;
    
    SynthEngine synthEngine2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (S1AudioProcessorEditor)
};
