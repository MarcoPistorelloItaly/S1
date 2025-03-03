/*
  ==============================================================================

    PresetSave.h
    Created: 4 Jan 2025 2:46:05pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FoldersList.h"
#include "Utilities.h"

//==============================================================================
/*
*/
class PresetSave  : public juce::Component,
                    public juce::Button::Listener,
                    public juce::TextEditor::Listener
{
public:
    PresetSave(S1AudioProcessor& p);
    ~PresetSave() override;
    
    void buttonClicked (juce::Button*) override;
    
    void textEditorTextChanged (juce::TextEditor& textEditor) override;
    void selectPresetFolder(std::string selectedFolderNameParam);

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void filterFoldersList(std::string);
    void refreshFoldersList();
    
    void clearForm();

private:
    
    juce::TextEditor presetName;
    juce::TextEditor presetCreatorName;
    std::string selectedFolderName;
    juce::TextEditor newFolderName;
    FoldersList foldersList;
    juce::TextButton saveButton;
    
    juce::TextEditor::LengthAndCharacterRestriction presetNameFilter;
    juce::TextEditor::InputFilter* inputFilter;
    
    Utilities utilities;
    
    S1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetSave)
};
