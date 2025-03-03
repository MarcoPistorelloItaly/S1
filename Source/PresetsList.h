/*
  ==============================================================================

    PresetsList.h
    Created: 4 Jan 2025 2:08:38pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utilities.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class PresetsList  : public juce::ListBox,
                     public juce::ListBoxModel
{
public:
    PresetsList(S1AudioProcessor& p);
    ~PresetsList() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    int getNumRows() override;

    void paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    
    void fillListData(std::map<juce::String, juce::var> presetsMap, int whatToShow, std::string filter, std::string exclude);
    
    void selectedRowsChanged (int lastRowSelected) override;
    
    void listBoxItemDoubleClicked (int row, const juce::MouseEvent&) override;
    
    std::map<int, std::string> presetsListData;
    
    void filterList(std::string filter);
    void refreshList();

private:
    Utilities utilities;
    S1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsList)
};
