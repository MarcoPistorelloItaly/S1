/*
  ==============================================================================

    FoldersList.cpp
    Created: 4 Jan 2025 2:06:01pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FoldersList.h"
#include "Utilities.h"

//==============================================================================
FoldersList::FoldersList(S1AudioProcessor& p, int foldersListTypeParam) :
processor(p)
{
    setModel(this);
    foldersListType = foldersListTypeParam;
    
    setSize(GLOBAL_WIDTH / 2, SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT - 300);
}

FoldersList::~FoldersList()
{
}

void FoldersList::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::red);
    std::cout << "FoldersList paint " << std::endl;
    ListBox::paint(g);
    g.fillAll (juce::Colours::red);
}

void FoldersList::resized ()
{
    ListBox::resized();
    
    if(foldersListType == FOLDERS_LIST_BROWSE_TYPE) {
        juce::Rectangle<int> area = getLocalBounds();
        area.setPosition(0, PROGRAM_SELECTOR_HEIGHT);
        setBounds(area);
        setSize(GLOBAL_WIDTH / 2, SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT - PROGRAM_SELECTOR_HEIGHT);
    }
}

int FoldersList::getNumRows()
{
    return int(listData.size());
}

void FoldersList::paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    g.fillAll(juce::Colours::black);
    if (rowIsSelected)
        g.fillAll (juce::Colours::lightblue);
    
    g.setColour (juce::Colours::grey);
    g.drawRect (g.getClipBounds(), 1);

    std::string someData = listData.at(rowNumber);
    
    g.setColour (juce::Colours::white);
    g.drawText (someData, 4, 0, width - 4, height, juce::Justification::centredLeft, true);

}

void FoldersList::fillListData(std::map<juce::String, juce::var> presetsMap, int whatToShow, std::string filter, std::string exclude) {
    //std::string *newListData = new std::string[presetsMap.size()];
    
    std::map<juce::String, juce::String> buffer;
    
    listData.clear();
    
    int index = 0;
    for(auto parametersGlobalMapIt = presetsMap.cbegin(); parametersGlobalMapIt != presetsMap.cend(); ++parametersGlobalMapIt)
    {
        //newListData->set
        
        //newListData[index] = parametersGlobalMapIt->first.toStdString();
        
        juce::String itemToInsert =  utilities.buildFolderName(parametersGlobalMapIt->first.toStdString());
        
        if(!filter.empty()) {
            if(itemToInsert.toStdString() != filter) {
                continue;
            }
        }
        
        if(!exclude.empty()) {
            if(itemToInsert.toStdString() == exclude) {
                continue;
            }
        }
        
        if(whatToShow == WHAT_TO_SHOW_PRESETS) {
            itemToInsert =  utilities.buildOnlyPatchName(parametersGlobalMapIt->first.toStdString());
        }
        
        if(buffer.find(itemToInsert) != buffer.end()) {
            continue;
        }
        
        buffer.insert(std::pair<juce::String,juce::String>(itemToInsert, itemToInsert));
        
        listData.insert(std::pair<int,std::string>(index, itemToInsert.toStdString() ));
        
        index++;
    }
}

void FoldersList::selectedRowsChanged (int lastRowSelected) {
    if(foldersListType == FOLDERS_LIST_BROWSE_TYPE) {
        std::string folderName = listData.at(lastRowSelected);
        processor.selectPresetFolder(folderName);
    }
}

void FoldersList::listBoxItemClicked (int row, const juce::MouseEvent&) {
    if(foldersListType == FOLDERS_LIST_SAVE_TYPE) {
        std::string folderName = listData.at(row);
        processor.selectSavePresetFolder(folderName);
    }
}

void FoldersList::clearSelectedItem() {
    //this->
    
}

void FoldersList::filterList(std::string filter) {
    this->fillListData(processor.getPresetsMap(), WHAT_TO_SHOW_FOLDERS, filter, "");
    this->updateContent();
}

void FoldersList::refreshList() {
    this->filterList("");
}
