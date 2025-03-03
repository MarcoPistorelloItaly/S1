/*
  ==============================================================================

    PresetSave.cpp
    Created: 4 Jan 2025 2:46:05pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetsSave.h"
#include "Utilities.h"

//==============================================================================
PresetSave::PresetSave(S1AudioProcessor& p) :
processor(p), foldersList(p, FoldersList::FOLDERS_LIST_SAVE_TYPE), presetNameFilter(NAME_MAX_LENGTH, NAME_ALLOWED_CHARACTERS)
{
    addAndMakeVisible(presetName);
    addAndMakeVisible(presetCreatorName);
    addAndMakeVisible(newFolderName);
    addAndMakeVisible(foldersList);
    addAndMakeVisible(saveButton);
    
    presetName.setSize(GLOBAL_WIDTH, 100);
    presetName.setTextToShowWhenEmpty("Preset Name", juce::Colours::grey);
    presetName.setBounds(STANDARD_PADDING, STANDARD_PADDING, INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT);
    
    inputFilter = &presetNameFilter;
    presetName.setInputFilter(inputFilter, false);
    
    presetCreatorName.setSize(GLOBAL_WIDTH, 100);
    presetCreatorName.setTextToShowWhenEmpty("Preset Creator", juce::Colours::grey);
    presetCreatorName.setBounds(STANDARD_PADDING, STANDARD_PADDING * 2 + INPUT_TEXT_HEIGHT, INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT);
    
    foldersList.setSize(GLOBAL_WIDTH, 100);
    foldersList.setBounds(STANDARD_PADDING, STANDARD_PADDING * 3 + INPUT_TEXT_HEIGHT * 2, INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT * 4);
    foldersList.fillListData(p.getPresetsMap(), 0, "", DEFAULT_PRESET_INIT_NAME);
    foldersList.updateContent();
    
    newFolderName.setSize(GLOBAL_WIDTH, 100);
    newFolderName.setTextToShowWhenEmpty("New Folder Name", juce::Colours::grey);
    newFolderName.setBounds(STANDARD_PADDING, STANDARD_PADDING * 3 + INPUT_TEXT_HEIGHT * 6, INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT);
    newFolderName.addListener(this);
    
    saveButton.setSize(INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT);
    saveButton.setButtonText("Save");
    saveButton.setBounds(STANDARD_PADDING, STANDARD_PADDING * 4 + INPUT_TEXT_HEIGHT * 7, INPUT_TEXT_WIDTH, INPUT_TEXT_HEIGHT);
    saveButton.addListener(this);
    //presetName.setFocusContainer(false);
    //presetName.setLineSpacing(1.5);
}

PresetSave::~PresetSave()
{
}

void PresetSave::paint (juce::Graphics& g)
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
    g.drawText ("PresetSave", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PresetSave::resized()
{
}

void PresetSave::buttonClicked (juce::Button* button)
{
    std::cout << presetName.getTextValue().toString() << std::endl;
    std::string presetNameValue = presetName.getTextValue().toString().toStdString();
    std::string presetCreatorNamealue = presetCreatorName.getTextValue().toString().toStdString();
    std::string newFolderNameValue = newFolderName.getTextValue().toString().toStdString();
    
    if(newFolderNameValue.empty()) {
        newFolderNameValue = selectedFolderName;
    }
    
    if(button == &saveButton)
    {
        utilities.createNewPresetFolder(newFolderNameValue);
        std::string newPresetJson = processor.buildPresetJSON(presetNameValue, newFolderNameValue, presetCreatorNamealue);
        utilities.writeNewPresetFile(presetNameValue, newFolderNameValue, presetCreatorNamealue, newPresetJson);
        processor.updatePresetsMap();
        processor.refreshFoldersAndPresets();
        processor.resetLayers();
        
        std::string presetComposedName = utilities.buildPresetComposedName(USER_APPLICATION_DATA_DIRECTORY_INDEX, newFolderNameValue, presetNameValue);
        processor.loadSettingsFromPresetComposedName(presetComposedName);
        processor.hidePresetsBrowser();
        
        this->clearForm();
    }
}

void PresetSave::selectPresetFolder(std::string selectedFolderNameParam) {
    std::cout << selectedFolderNameParam << std::endl;
    selectedFolderName = selectedFolderNameParam;
    newFolderName.clear();
}

void PresetSave::textEditorTextChanged (juce::TextEditor& textEditor)
{
    std::cout << textEditor.getText() << std::endl;
    foldersList.clearSelectedItem();
}

void PresetSave::filterFoldersList(std::string filter) {
    foldersList.filterList(filter);
}

void PresetSave::refreshFoldersList() {
    foldersList.refreshList();
}

void PresetSave::clearForm() {
    presetName.clear();
    newFolderName.clear();
    presetCreatorName.clear();
    foldersList.clearSelectedItem();
    foldersList.refreshList();
    foldersList.repaint();
}
