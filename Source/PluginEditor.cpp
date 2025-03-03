/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
S1AudioProcessorEditor::S1AudioProcessorEditor (S1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), presetSave(p), presetsBrowser(p), programSelector(p), synthEngine1(p, 1), synthEngine2(p, 2)
{
    addAndMakeVisible(&presetsBrowser);
    
    addAndMakeVisible(&presetSave);
    
    addAndMakeVisible(&programSelector);
    
    addAndMakeVisible(&synthEngine1);
    
    addAndMakeVisible(&synthEngine2);
    
    setSize (GLOBAL_WIDTH, SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT + PROGRAM_SELECTOR_HEIGHT);
}

S1AudioProcessorEditor::~S1AudioProcessorEditor()
{
}

//==============================================================================
void S1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Marco Pysto S1", getLocalBounds(), juce::Justification::centred, 1);
}

void S1AudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    
    area.setPosition(0, PROGRAM_SELECTOR_HEIGHT);
    
    const int engineWidth = SYNTH_ENGINE_WIDTH;
    const int engineHeight = SYNTH_ENGINE_HEIGHT;
    
    presetsBrowser.setBounds(area.removeFromTop(SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT));
    
    juce::Rectangle<int> presetSaveArea = getLocalBounds();
    presetSaveArea.setPosition(0, PROGRAM_SELECTOR_HEIGHT);
    presetSave.setBounds(presetSaveArea.removeFromTop(SYNTH_ENGINE_HEIGHT + SYNTH_ENGINE_HEIGHT));
    
    juce::Rectangle<int> area1 = getLocalBounds();
    area1.setTop(PROGRAM_SELECTOR_HEIGHT);
    synthEngine1.setBounds(area1.removeFromLeft(engineWidth).removeFromTop(engineHeight));
    
    
    juce::Rectangle<int> area2 = getLocalBounds();
    area2.setTop(engineHeight + PROGRAM_SELECTOR_HEIGHT);
    juce::Rectangle<int> synthEngine2Area = area2.removeFromLeft(engineWidth).removeFromTop(engineHeight);
    synthEngine2.setBounds(synthEngine2Area);
    
    /*
    Rectangle<int> area3 = getLocalBounds();
    area3.setTop(engineHeight * 2);
    Rectangle<int> synthEngine3Area = area3.removeFromLeft(200).removeFromTop(engineHeight);
    mixerGUI.setBounds(synthEngine3Area);
    
    Rectangle<int> area4 = getLocalBounds();
    area4.setTop(engineHeight * 3);
    Rectangle<int> noiseGeneratorArea = area4.removeFromLeft(200).removeFromTop(engineHeight);
    noiseGenerator.setBounds(noiseGeneratorArea);*/
}

ProgramSelector& S1AudioProcessorEditor::getProgramSelector()
{
    return programSelector;
}

void S1AudioProcessorEditor::showPresetsBrowser()
{
    resetLayers();
    presetsBrowser.toFront(true);
    programSelector.setPresetsBrowserShown(1);
}

void S1AudioProcessorEditor::hidePresetsBrowser()
{
    resetLayers();
    presetsBrowser.toBack();
    programSelector.setPresetsBrowserShown(0);
}

void S1AudioProcessorEditor::showPresetSave()
{
    resetLayers();
    presetSave.toFront(true);
    programSelector.setPresetSaveShown(1);
}

void S1AudioProcessorEditor::hidePresetSave()
{
    resetLayers();
    presetSave.toBack();
    programSelector.setPresetSaveShown(0);
}

void S1AudioProcessorEditor::selectPresetFolder(std::string folderName) {
    presetsBrowser.filterPresetsList(folderName);
    return;
}

void S1AudioProcessorEditor::selectSavePresetFolder(std::string folderName) {
    presetSave.selectPresetFolder(folderName);
    return;
}

void S1AudioProcessorEditor::changeProgramSelectorName(std::string newPresetName) {
    programSelector.changeProgramSelectorName(newPresetName);
    return;
}

void S1AudioProcessorEditor::refreshFoldersAndPresets() {
    presetsBrowser.refreshFoldersList();
    presetsBrowser.refreshPresetsList();
    presetSave.refreshFoldersList();
}

void S1AudioProcessorEditor::resetLayers() {
    presetsBrowser.toBack();
    presetSave.toBack();
    synthEngine1.toFront(true);
    synthEngine2.toFront(true);
    programSelector.setPresetSaveShown(0);
    programSelector.setPresetsBrowserShown(0);
}

void S1AudioProcessorEditor::aaa() {
    /*
    std::cout << "visible . " << presetsBrowser.isVisible() << std::endl;
    std::cout << "shown . " << presetsBrowser.isShowing() << std::endl;
    std::cout << "opaque . " << presetsBrowser.isOpaque() << std::endl;
     */
}
