/*
  ==============================================================================

    PresetBrowser.cpp
    Created: 4 Jan 2025 2:03:31pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetsBrowser.h"

//==============================================================================
PresetsBrowser::PresetsBrowser(S1AudioProcessor& p) :
processor(p), foldersList(p, FoldersList::FOLDERS_LIST_BROWSE_TYPE), presetsList(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(GLOBAL_WIDTH, SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT);
    
    addAndMakeVisible(foldersList);
    addAndMakeVisible(presetsList);
    
    foldersList.fillListData(p.getPresetsMap(), WHAT_TO_SHOW_FOLDERS, "", "");
    presetsList.fillListData(p.getPresetsMap(), WHAT_TO_SHOW_PRESETS, "", "");
    
    foldersList.setSize(GLOBAL_WIDTH / 2, SYNTH_ENGINE_HEIGHT * 2);
    
    juce::Rectangle<int> area = getLocalBounds();
    area.setPosition(GLOBAL_WIDTH / 2, 0);
    presetsList.setSize(GLOBAL_WIDTH / 2, SYNTH_ENGINE_HEIGHT * 2);
    presetsList.setBounds(area);
    
    foldersList.updateContent();
    presetsList.updateContent();
    
    presetsLabel.setText("Choose a Folder", juce::dontSendNotification);
    presetsLabel.setJustificationType(juce::Justification::centred);
    presetsLabel.setSize(GLOBAL_WIDTH / 2, PROGRAM_SELECTOR_HEIGHT);
    addAndMakeVisible(presetsLabel);
    
    foldersLabel.setText("Choose a Preset", juce::dontSendNotification);
    foldersLabel.setJustificationType(juce::Justification::centred);
    foldersLabel.setCentrePosition(GLOBAL_WIDTH / 2, 0);
    foldersLabel.setSize(GLOBAL_WIDTH / 2, PROGRAM_SELECTOR_HEIGHT);
    addAndMakeVisible(foldersLabel);

}

PresetsBrowser::~PresetsBrowser()
{
}

void PresetsBrowser::paint (juce::Graphics& g)
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
    g.drawText ("PresetsBrowser", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    foldersList.updateContent();
    
    //if (auto* m = foldersList.getModel())
        //m->paintListBoxItem (0, g, getWidth(), getHeight(), true);
}

void PresetsBrowser::resized()
{
    foldersList.resized();
    presetsList.resized();
}

void PresetsBrowser::filterPresetsList(std::string filter) {
    presetsList.filterList(filter);
}

void PresetsBrowser::refreshPresetsList() {
    presetsList.refreshList();
}

void PresetsBrowser::filterFoldersList(std::string filter) {
    foldersList.filterList(filter);
}

void PresetsBrowser::refreshFoldersList() {
    foldersList.refreshList();
}
