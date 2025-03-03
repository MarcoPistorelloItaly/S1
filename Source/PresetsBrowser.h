/*
  ==============================================================================

    PresetBrowser.h
    Created: 4 Jan 2025 2:03:31pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FoldersList.h"
#include "PresetsList.h"

//==============================================================================
/*
*/
class PresetsBrowser  : public juce::Component
{
public:
    PresetsBrowser(S1AudioProcessor& p);
    ~PresetsBrowser() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void filterPresetsList(std::string);
    void refreshPresetsList();
    
    void filterFoldersList(std::string);
    void refreshFoldersList();
    
    juce::Label presetsLabel;
    juce::Label foldersLabel;

private:
    
    S1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsBrowser)

public:
    FoldersList foldersList;
    PresetsList presetsList;
};
