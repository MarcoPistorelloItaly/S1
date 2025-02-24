/*
  ==============================================================================

    FoldersList.h
    Created: 4 Jan 2025 2:06:01pm
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
class FoldersList  : public juce::ListBox,
                    juce::ListBoxModel
{
public:
    
    enum { FOLDERS_LIST_BROWSE_TYPE = 1,
            FOLDERS_LIST_SAVE_TYPE = 2
    };
    
    FoldersList(S1AudioProcessor& p, int foldersListTypeParam);
    ~FoldersList() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;

    void paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    
    void fillListData(std::map<juce::String, juce::var> presetsMap, int whatToShow, std::string filter, std::string exclude);
    
    void selectedRowsChanged (int lastRowSelected) override;
    
    void listBoxItemClicked (int row, const juce::MouseEvent&) override;
    
    void clearSelectedItem();
    
    std::map<int, std::string> listData;
    
    int foldersListType;
    
    void filterList(std::string filter);
    void refreshList();

private:
    Utilities utilities;
    Constants constants;
    
    S1AudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldersList)
};
