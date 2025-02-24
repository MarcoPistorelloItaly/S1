/*
  ==============================================================================

    PresetsList.cpp
    Created: 4 Jan 2025 2:08:38pm
    Author:  Marco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetsList.h"

//==============================================================================
PresetsList::PresetsList(S1AudioProcessor& p) :
processor(p)
{
    setModel(this);
}

PresetsList::~PresetsList()
{
}

void PresetsList::paint (juce::Graphics& g)
{
    /*
    g.fillAll (Colours::red);
    std::cout << "PresetsList paint " << std::endl;
    //ListBox::paint(g);
    g.fillAll (Colours::red);*/
}

void PresetsList::resized ()
{
    ListBox::resized();
    juce::Rectangle<int> area = getLocalBounds();
    area.setPosition(GLOBAL_WIDTH / 2, PROGRAM_SELECTOR_HEIGHT);
    setBounds(area);
    setSize(GLOBAL_WIDTH / 2, SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT - PROGRAM_SELECTOR_HEIGHT);
}

int PresetsList::getNumRows()
{
    return int(presetsListData.size());
}

void PresetsList::paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    g.fillAll(juce::Colours::black);
    if (rowIsSelected)
        g.fillAll (juce::Colours::lightblue);
    
    g.setColour (juce::Colours::grey);
    g.drawRect (g.getClipBounds(), 1);

    std::string someData = utilities.buildOnlyPatchName(presetsListData.at(rowNumber)).toStdString();
    
    //std::cout << "someData - " << rowNumber << "  -  " << someData << std::endl;

    g.setColour (juce::Colours::white);
    g.drawText (someData, 4, 0, width - 4, height, juce::Justification::centredLeft, true);

}

void PresetsList::fillListData(std::map<juce::String, juce::var> presetsMap, int whatToShow, std::string filter, std::string exclude) {
    //std::string *newListData = new std::string[presetsMap.size()];
    
    std::map<juce::String, juce::String> buffer;
    
    int index = 0;
    
    presetsListData.clear();
    
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
        
        if(whatToShow == 1) {
            itemToInsert =  /*utilities.buildOnlyPatchName(*/parametersGlobalMapIt->first.toStdString()/*)*/;
        }
        
        if(buffer.find(itemToInsert) != buffer.end()) {
            continue;
        }
        
        buffer.insert(std::pair<juce::String,juce::String>(itemToInsert, itemToInsert));
        
        presetsListData.insert(std::pair<int,std::string>(index, itemToInsert.toStdString() ));
        index++;
    }
}

void PresetsList::selectedRowsChanged (int lastRowSelected) {
    std::string folderName = presetsListData.at(lastRowSelected);
}

void PresetsList::listBoxItemDoubleClicked (int row, const juce::MouseEvent&) {
    std::string presetComposedName = presetsListData.at(row);
    processor.loadSettingsFromPresetComposedName(presetComposedName);
    processor.hidePresetsBrowser();
    
    /*
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)processor.getActiveEditor();
    pluginEditor->getProgramSelector().setPresetsBrowserShown(0);
     */
}

void PresetsList::filterList(std::string filter) {
    this->fillListData(processor.getPresetsMap(), WHAT_TO_SHOW_PRESETS, filter, "");
    this->updateContent();
    this->repaint();
}

void PresetsList::refreshList() {
    this->filterList("");
}
