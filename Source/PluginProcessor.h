/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"
#include "PresetsUtilities.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Utilities.h"

//==============================================================================
/**
*/
class S1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    S1AudioProcessor();
    ~S1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    std::string movePresets(int direction);
    
    void showPresetsBrowser();
    void hidePresetsBrowser();
    void showPresetSave();
    void hidePresetSave();
    
    juce::AudioProcessorValueTreeState treeState;
    std::atomic<float>* attack1Parameter = nullptr;
    std::atomic<float>* decay1Parameter = nullptr;
    std::atomic<float>* sustain1Parameter = nullptr;
    std::atomic<float>* release1Parameter = nullptr;
    
    std::atomic<float>* attack2Parameter = nullptr;
    std::atomic<float>* decay2Parameter = nullptr;
    std::atomic<float>* sustain2Parameter = nullptr;
    std::atomic<float>* release2Parameter = nullptr;
    
    std::atomic<float>* waveType1Parameter = nullptr;
    std::atomic<float>* waveType2Parameter = nullptr;
    
    std::atomic<float>* level1Parameter = nullptr;
    std::atomic<float>* level2Parameter = nullptr;
    
    std::atomic<float>* filterCutoffDial1Parameter = nullptr;
    std::atomic<float>* filterResDial1Parameter = nullptr;
    std::atomic<float>* filterMenu1Parameter = nullptr;
    std::atomic<float>* filterAttack1Parameter = nullptr;
    
    std::atomic<float>* filterCutoffDial2Parameter = nullptr;
    std::atomic<float>* filterResDial2Parameter = nullptr;
    std::atomic<float>* filterMenu2Parameter = nullptr;
    std::atomic<float>* filterAttack2Parameter = nullptr;
    
    std::atomic<float>* drive1Parameter = nullptr;
    std::atomic<float>* range1Parameter = nullptr;
    std::atomic<float>* blend1Parameter = nullptr;
    std::atomic<float>* volume1Parameter = nullptr;
    
    std::atomic<float>* drive2Parameter = nullptr;
    std::atomic<float>* range2Parameter = nullptr;
    std::atomic<float>* blend2Parameter = nullptr;
    std::atomic<float>* volume2Parameter = nullptr;
    
    std::atomic<bool>* distortion1SwitchParameter = nullptr;
    std::atomic<bool>* distortion2SwitchParameter = nullptr;
    
    std::atomic<float>* noiseGeneratorSwitchParameter = nullptr;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    std::string getCurrentPresetComposedName();
    
    std::map<juce::String, juce::var> getPresetsMap();
    
    void selectPresetFolder(std::string folderName);
    void selectSavePresetFolder(std::string folderName);
    
    void loadSettingsFromPresetComposedName(std::string);
    
    std::string buildPresetJSON(std::string newPresetName, std::string newPresetFolderName, std::string newPresetCreatorName, bool loadDefault = false);
    
    void resetLayers();
    
    void refreshFoldersAndPresets();
    
    void updatePresetsMap();
    
    std::atomic<float>* filter1SwitchParameter = nullptr;
    std::atomic<float>* filter2SwitchParameter = nullptr;

private:
    //==============================================================================
    
    juce::Synthesiser mySynth;
    juce::Synthesiser mySynth2;
    SynthVoice* myVoice;
    
    void updateFilter();
    

    double lastSampleRate;
    
    PresetsUtilities presetsUtilities;
    
    /*
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, dsp::StateVariableFilter::Parameters<float>> stateVariableFilter1;
    
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, dsp::StateVariableFilter::Parameters<float>> stateVariableFilter2;
     */
    /*
    IIRFilter* iirFilter;
     
     */
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
    
    juce::ADSR filterADSR;
    juce::ADSR::Parameters filterADSRparameters;
    
    juce::dsp::StateVariableTPTFilterType filter1Type;
    juce::dsp::StateVariableTPTFilterType filter2Type;
    
    Utilities utilities;
    
    std::string currentPresetComposedName;
    void loadSettingsFromPresetJSON(juce::var);
    
    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb leftReverb, rightReverb;
    
    /*
    AudioBuffer<float> mDelayBuffer;
    int mWritePosition { 0 };
     */
    
    Constants* constants;
    
    inline bool ends_with(std::string const & value, std::string const & ending);
    
    std::map<juce::String, juce::var> presetsMap;
    
    void aaa();
    
    
    
    std::map<juce::String, juce::var> insertInitPresetMap(std::map<juce::String, juce::var>);
    
    std::map<juce::String, juce::var> iterateFolderAndInsertPresetMap(juce::File,
                                                                std::map<juce::String, juce::var>,
                                                                Utilities,
                                                                std::string folderIndex);
    
    void installPresets();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (S1AudioProcessor)
};
