/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
S1AudioProcessor::S1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", { createParameterLayout()})
#endif
{
    installPresets();
    
    //installWavetableWaveforms();
    
    mySynth.clearVoices();
    
    for(int i = 0; i < 20; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    
    mySynth.clearSounds();
    
    mySynth.addSound(new SynthSound());
    
    mySynth2.clearVoices();
    
    for(int i = 0; i < 20; i++) {
        mySynth2.addVoice(new SynthVoice());
    }
    
    mySynth2.clearSounds();
    
    mySynth2.addSound(new SynthSound());
    
    updatePresetsMap();
    
    //loadSettingsFromPresetComposedName(presetsUtilities.buildInitPresetComposedName());
    
    constants = new Constants();
}

juce::AudioProcessorValueTreeState::ParameterLayout S1AudioProcessor::createParameterLayout()
{
    //TODO: Move following array creation in dedicated file
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    constants = new Constants();
    
    auto attack1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_1_ATTACK_ID,  PARAM_VERSION_HINT },
                                                                     ADSR_1_ATTACK_NAME,
                                                                        juce::NormalisableRange<float> (constants->getParamValue(ADSR_1_ATTACK_ID, "MIN"), constants->getParamValue(ADSR_1_ATTACK_ID, "MAX")), constants->getParamValue(ADSR_1_ATTACK_ID, "DEFAULT"));
                                                            
    auto decay1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_1_DECAY_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(ADSR_1_DECAY_ID, "NAME"),
                                                              constants->getParamValue(ADSR_1_DECAY_ID, "MIN"),
                                                              constants->getParamValue(ADSR_1_DECAY_ID, "MAX"),
                                                              constants->getParamValue(ADSR_1_DECAY_ID, "DEFAULT"));
    
    auto sustain1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_1_SUSTAIN_ID, PARAM_VERSION_HINT },
                                                                constants->getParamValueString(ADSR_1_SUSTAIN_ID, "NAME"),
                                                                constants->getParamValue(ADSR_1_SUSTAIN_ID, "MIN"),
                                                                constants->getParamValue(ADSR_1_SUSTAIN_ID, "MAX"),
                                                                constants->getParamValue(ADSR_1_SUSTAIN_ID, "DEFAULT"));
    
    auto release1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_1_RELEASE_ID, PARAM_VERSION_HINT },
                                                                constants->getParamValueString(ADSR_1_RELEASE_ID, "NAME"),
                                                                constants->getParamValue(ADSR_1_RELEASE_ID, "MIN"),
                                                                constants->getParamValue(ADSR_1_RELEASE_ID, "MAX"),
                                                                constants->getParamValue(ADSR_1_RELEASE_ID, "DEFAULT"));
    
    auto attack2Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_2_ATTACK_ID, PARAM_VERSION_HINT },
                                                                constants->getParamValueString(ADSR_2_ATTACK_ID, "NAME"),
                                                                constants->getParamValue(ADSR_2_ATTACK_ID, "MIN"),
                                                                constants->getParamValue(ADSR_2_ATTACK_ID, "MAX"),
                                                                constants->getParamValue(ADSR_2_ATTACK_ID, "DEFAULT"));
    
    auto decay2Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_2_DECAY_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(ADSR_2_DECAY_ID, "NAME"),
                                                              constants->getParamValue(ADSR_2_DECAY_ID, "MIN"),
                                                              constants->getParamValue(ADSR_2_DECAY_ID, "MAX"),
                                                              constants->getParamValue(ADSR_2_DECAY_ID, "DEFAULT"));
    
    auto sustain2Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_2_SUSTAIN_ID, PARAM_VERSION_HINT },
                                                                constants->getParamValueString(ADSR_2_SUSTAIN_ID, "NAME"),
                                                                constants->getParamValue(ADSR_2_SUSTAIN_ID, "MIN"),
                                                                constants->getParamValue(ADSR_2_SUSTAIN_ID, "MAX"),
                                                                constants->getParamValue(ADSR_2_SUSTAIN_ID, "DEFAULT"));
    
    auto release2Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ADSR_2_RELEASE_ID, PARAM_VERSION_HINT },
                                                                constants->getParamValueString(ADSR_2_RELEASE_ID, "NAME"),
                                                                constants->getParamValue(ADSR_2_RELEASE_ID, "MIN"),
                                                                constants->getParamValue(ADSR_2_RELEASE_ID, "MAX"),
                                                                constants->getParamValue(ADSR_2_RELEASE_ID, "DEFAULT"));
    
    auto waveType1Param = std::make_unique<juce::AudioParameterInt> (juce::ParameterID { WAVE_TYPE_1_ID, PARAM_VERSION_HINT },
                                                               constants->getParamValueString(WAVE_TYPE_1_ID, "NAME"),
                                                               constants->getParamValue(WAVE_TYPE_1_ID, "MIN"),
                                                               constants->getParamValue(WAVE_TYPE_1_ID, "MAX"),
                                                               constants->getParamValue(WAVE_TYPE_1_ID, "DEFAULT"));
    
    auto waveType2Param = std::make_unique<juce::AudioParameterInt> (juce::ParameterID { WAVE_TYPE_2_ID, PARAM_VERSION_HINT },
                                                               constants->getParamValueString(WAVE_TYPE_2_ID, "NAME"),
                                                               constants->getParamValue(WAVE_TYPE_2_ID, "MIN"),
                                                               constants->getParamValue(WAVE_TYPE_2_ID, "MAX"),
                                                               constants->getParamValue(WAVE_TYPE_2_ID, "DEFAULT"));
    
    auto level1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { LEVEL_1_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(LEVEL_1_ID, "NAME"),
                                                              constants->getParamValue(LEVEL_1_ID, "MIN"),
                                                              constants->getParamValue(LEVEL_1_ID, "MAX"),
                                                              constants->getParamValue(LEVEL_1_ID, "DEFAULT"));
    
    auto level2Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { LEVEL_2_ID, PARAM_VERSION_HINT },
                                                             constants->getParamValueString(LEVEL_2_ID, "NAME"),
                                                             constants->getParamValue(LEVEL_2_ID, "MIN"),
                                                             constants->getParamValue(LEVEL_2_ID, "MAX"),
                                                             constants->getParamValue(LEVEL_2_ID, "DEFAULT"));
    
    auto drive1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { DISTORTION_1_DRIVE_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(DISTORTION_1_DRIVE_ID, "NAME"),
                                                              constants->getParamValue(DISTORTION_1_DRIVE_ID, "MIN"),
                                                              constants->getParamValue(DISTORTION_1_DRIVE_ID, "MAX"),
                                                              constants->getParamValue(DISTORTION_1_DRIVE_ID, "DEFAULT"));
    
    auto range1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { DISTORTION_1_RANGE_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(DISTORTION_1_RANGE_ID, "NAME"),
                                                              constants->getParamValue(DISTORTION_1_RANGE_ID, "MIN"),
                                                              constants->getParamValue(DISTORTION_1_RANGE_ID, "MAX"),
                                                              constants->getParamValue(DISTORTION_1_RANGE_ID, "DEFAULT"));
    
    auto blend1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { DISTORTION_1_BLEND_ID, PARAM_VERSION_HINT },
                                                              constants->getParamValueString(DISTORTION_1_BLEND_ID, "NAME"),
                                                              constants->getParamValue(DISTORTION_1_BLEND_ID, "MIN"),
                                                              constants->getParamValue(DISTORTION_1_BLEND_ID, "MAX"),
                                                              constants->getParamValue(DISTORTION_1_BLEND_ID, "DEFAULT"));
    
    auto volume1Param = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { DISTORTION_1_VOLUME_ID, PARAM_VERSION_HINT },
                                                               constants->getParamValueString(DISTORTION_1_VOLUME_ID, "NAME"),
                                                               constants->getParamValue(DISTORTION_1_VOLUME_ID, "MIN"),
                                                               constants->getParamValue(DISTORTION_1_VOLUME_ID, "MAX"),
                                                               constants->getParamValue(DISTORTION_1_VOLUME_ID, "DEFAULT"));
    
    auto filterCutoffDial1Parameter = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { FILTER_1_CUTOFF_ID, PARAM_VERSION_HINT },
         constants->getParamValueString(FILTER_1_CUTOFF_ID, "NAME"),
         constants->getParamValue(FILTER_1_CUTOFF_ID, "MIN"),
         constants->getParamValue(FILTER_1_CUTOFF_ID, "MAX"),
         constants->getParamValue(FILTER_1_CUTOFF_ID, "DEFAULT"));
    
    // NormalisableRange<float> filterRes1Range(FILTER_RES_DIAL_MIN, FILTER_RES_DIAL_MAX);
    
    auto filterResDial1Parameter = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { FILTER_1_RES_ID, PARAM_VERSION_HINT },
          constants->getParamValueString(FILTER_1_RES_ID, "NAME"),
          constants->getParamValue(FILTER_1_RES_ID, "MIN"),
          constants->getParamValue(FILTER_1_RES_ID, "MAX"),
          constants->getParamValue(FILTER_1_RES_ID, "DEFAULT"));
    
    auto filterMenu1Parameter = std::make_unique<juce::AudioParameterInt> (
        juce::ParameterID { FILTER_1_TYPE_ID, PARAM_VERSION_HINT },
         constants->getParamValueString(FILTER_1_TYPE_ID, "NAME"),
         constants->getParamValue(FILTER_1_TYPE_ID, "MIN"),
         constants->getParamValue(FILTER_1_TYPE_ID, "MAX"),
         constants->getParamValue(FILTER_1_TYPE_ID, "DEFAULT"));
    
    auto drive2Param = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { DISTORTION_2_DRIVE_ID, PARAM_VERSION_HINT },
          constants->getParamValueString(DISTORTION_2_DRIVE_ID, "NAME"),
          constants->getParamValue(DISTORTION_2_DRIVE_ID, "MIN"),
          constants->getParamValue(DISTORTION_2_DRIVE_ID, "MAX"),
          constants->getParamValue(DISTORTION_2_DRIVE_ID, "DEFAULT"));
    
    auto range2Param = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { DISTORTION_2_RANGE_ID, PARAM_VERSION_HINT },
          constants->getParamValueString(DISTORTION_2_RANGE_ID, "NAME"),
          constants->getParamValue(DISTORTION_2_RANGE_ID, "MIN"),
          constants->getParamValue(DISTORTION_2_RANGE_ID, "MAX"),
          constants->getParamValue(DISTORTION_2_RANGE_ID, "DEFAULT"));
    
    auto blend2Param = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { DISTORTION_2_BLEND_ID, PARAM_VERSION_HINT },
          constants->getParamValueString(DISTORTION_2_BLEND_ID, "NAME"),
          constants->getParamValue(DISTORTION_2_BLEND_ID, "MIN"),
          constants->getParamValue(DISTORTION_2_BLEND_ID, "MAX"),
          constants->getParamValue(DISTORTION_2_BLEND_ID, "DEFAULT"));
    
    auto volume2Param = std::make_unique<juce::AudioParameterFloat> (
             juce::ParameterID { DISTORTION_2_VOLUME_ID, PARAM_VERSION_HINT },
       constants->getParamValueString(DISTORTION_2_VOLUME_ID, "NAME"),
       constants->getParamValue(DISTORTION_2_VOLUME_ID, "MIN"),
       constants->getParamValue(DISTORTION_2_VOLUME_ID, "MAX"),
       constants->getParamValue(DISTORTION_2_VOLUME_ID, "DEFAULT"));
    
    auto filterCutoffDial2Parameter = std::make_unique<juce::AudioParameterFloat> (
       juce::ParameterID { FILTER_2_CUTOFF_ID, PARAM_VERSION_HINT },
         constants->getParamValueString(FILTER_2_CUTOFF_ID, "NAME"),
         constants->getParamValue(FILTER_2_CUTOFF_ID, "MIN"),
         constants->getParamValue(FILTER_2_CUTOFF_ID, "MAX"),
         constants->getParamValue(FILTER_2_CUTOFF_ID, "DEFAULT"));
    
    auto filterResDial2Parameter = std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { FILTER_2_RES_ID, PARAM_VERSION_HINT },
          constants->getParamValueString(FILTER_2_RES_ID, "NAME"),
          constants->getParamValue(FILTER_2_RES_ID, "MIN"),
          constants->getParamValue(FILTER_2_RES_ID, "MAX"),
          constants->getParamValue(FILTER_2_RES_ID, "DEFAULT"));
    
    auto filterMenu2Parameter = std::make_unique<juce::AudioParameterInt> (
        juce::ParameterID { FILTER_2_TYPE_ID, PARAM_VERSION_HINT },
         constants->getParamValueString(FILTER_2_TYPE_ID, "NAME"),
         constants->getParamValue(FILTER_2_TYPE_ID, "MIN"),
         constants->getParamValue(FILTER_2_TYPE_ID, "MAX"),
         constants->getParamValue(FILTER_2_TYPE_ID, "DEFAULT"));
    
    // TODO: Should I sync with the above syntax?
    auto distortion1SwitchParameter = std::make_unique<juce::AudioParameterInt> (
         juce::ParameterID { DISTORTION_1_SWITCH_ID, PARAM_VERSION_HINT },
                                                                           DISTORTION_1_SWITCH_NAME,
                                                                    FILTER_MENU_MIN,
                                                                    FILTER_MENU_MAX,
                                                                    FILTER_MENU_DEFAULT);
    
    auto distortion2SwitchParameter = std::make_unique<juce::AudioParameterInt> (
         juce::ParameterID { DISTORTION_2_SWITCH_ID, PARAM_VERSION_HINT },
                                                                           DISTORTION_2_SWITCH_NAME,
                                                                    FILTER_MENU_MIN,
                                                                    FILTER_MENU_MAX,
                                                                    FILTER_MENU_DEFAULT);
    
    auto noiseGeneratorSwitchParameter = std::make_unique<juce::AudioParameterFloat> (
      juce::ParameterID { NOISE_GENERATOR_SWITCH_ID, PARAM_VERSION_HINT },
                                                                    NOISE_GENERATOR_SWITCH_NAME,
                                                                    FILTER_MENU_MIN,
                                                                    FILTER_MENU_MAX,
                                                                    FILTER_MENU_DEFAULT);
    
    auto filterAttack1 = std::make_unique<juce::AudioParameterFloat> (
          juce::ParameterID { FILTER_1_ATTACK_ID, PARAM_VERSION_HINT },
            constants->getParamValueString(FILTER_1_ATTACK_ID, "NAME"),
            constants->getParamValue(FILTER_1_ATTACK_ID, "MIN"),
            constants->getParamValue(FILTER_1_ATTACK_ID, "MAX"),
            constants->getParamValue(FILTER_1_ATTACK_ID, "DEFAULT"));
    
    auto filterAttack2 = std::make_unique<juce::AudioParameterFloat> (
          juce::ParameterID { FILTER_2_ATTACK_ID, PARAM_VERSION_HINT },
            constants->getParamValueString(FILTER_2_ATTACK_ID, "NAME"),
            constants->getParamValue(FILTER_2_ATTACK_ID, "MIN"),
            constants->getParamValue(FILTER_2_ATTACK_ID, "MAX"),
            constants->getParamValue(FILTER_2_ATTACK_ID, "DEFAULT"));
    
    auto filter1SwitchParameter = std::make_unique<juce::AudioParameterInt> (
         juce::ParameterID { FILTER_1_SWITCH_ID, PARAM_VERSION_HINT },
           constants->getParamValueString(FILTER_1_SWITCH_ID, "NAME"),
           constants->getParamValue(FILTER_1_SWITCH_ID, "MIN"),
           constants->getParamValue(FILTER_1_SWITCH_ID, "MAX"),
           constants->getParamValue(FILTER_1_SWITCH_ID, "DEFAULT"));
    
    auto filter2SwitchParameter = std::make_unique<juce::AudioParameterInt> (
         juce::ParameterID { FILTER_2_SWITCH_ID, PARAM_VERSION_HINT },
           constants->getParamValueString(FILTER_2_SWITCH_ID, "NAME"),
           constants->getParamValue(FILTER_2_SWITCH_ID, "MIN"),
           constants->getParamValue(FILTER_2_SWITCH_ID, "MAX"),
           constants->getParamValue(FILTER_2_SWITCH_ID, "DEFAULT"));
    
    // TODO: Attention here!!!!!
    //std::cout << "selectedProgramParameter " << selectedProgramParameter->isAutomatable() << std::endl;
    //treeState.createAndAddParameter(selectedProgramParameter2);
    
    params.push_back(std::move(attack1Param));
    
    params.push_back(std::move(decay1Param));
    params.push_back(std::move(release1Param));
    params.push_back(std::move(sustain1Param));
    params.push_back(std::move(waveType1Param));
    params.push_back(std::move(level1Param));
    params.push_back(std::move(drive1Param));
    params.push_back(std::move(range1Param));
    params.push_back(std::move(blend1Param));
    params.push_back(std::move(volume1Param));
    params.push_back(std::move(filterCutoffDial1Parameter));
    params.push_back(std::move(filterResDial1Parameter));
    params.push_back(std::move(filterMenu1Parameter));
    params.push_back(std::move(distortion1SwitchParameter));
    params.push_back(std::move(filter1SwitchParameter));
    
    params.push_back(std::move(attack2Param));
    params.push_back(std::move(decay2Param));
    params.push_back(std::move(release2Param));
    params.push_back(std::move(sustain2Param));
    params.push_back(std::move(waveType2Param));
    params.push_back(std::move(level2Param));
    params.push_back(std::move(drive2Param));
    params.push_back(std::move(range2Param));
    params.push_back(std::move(blend2Param));
    params.push_back(std::move(volume2Param));
    params.push_back(std::move(filterCutoffDial2Parameter));
    params.push_back(std::move(filterResDial2Parameter));
    params.push_back(std::move(filterMenu2Parameter));
    params.push_back(std::move(distortion2SwitchParameter));
    params.push_back(std::move(filter2SwitchParameter));
    
    params.push_back(std::move(filterAttack1));
    params.push_back(std::move(filterAttack2));
    
    params.push_back(std::move(noiseGeneratorSwitchParameter));
    
    return {params.begin(), params.end()};
}

S1AudioProcessor::~S1AudioProcessor()
{
}

//==============================================================================
const juce::String S1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool S1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool S1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool S1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double S1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int S1AudioProcessor::getNumPrograms()
{
    return 100;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int S1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void S1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String S1AudioProcessor::getProgramName (int index)
{
    return {};
}

void S1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void S1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::ignoreUnused(samplesPerBlock);
    
    if(sampleRate != lastSampleRate) {
        lastSampleRate = sampleRate;
        mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
        mySynth2.setCurrentPlaybackSampleRate(lastSampleRate);
        
        juce::dsp::ProcessSpec spec;
        
        spec.sampleRate = sampleRate;
        spec.maximumBlockSize = samplesPerBlock;
        spec.numChannels = 1;
        
        leftReverb.prepare(spec);
        rightReverb.prepare(spec);
    }
    
    updateFilter();
    
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            voice->setSampleRate(sampleRate);
            voice->setBufferSize(samplesPerBlock);
            voice->setNumChannels(getTotalNumOutputChannels());
            voice->prepareFilter();
            voice->setFilterType(filter1Type);
            voice->setFilterRes(filterResDial1Parameter);
            voice->setFilterSwitch(filter1SwitchParameter);
            
            voice->updateVoice(lastSampleRate);
            
            voice->setIndex(i);
        }
    }
    for (int i = 0; i < mySynth2.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(mySynth2.getVoice(i)))
        {
            voice->setSampleRate(sampleRate);
            voice->setBufferSize(samplesPerBlock);
            voice->setNumChannels(getTotalNumOutputChannels());
            voice->prepareFilter();
            voice->setFilterType(filter2Type);
            voice->setFilterRes(filterResDial2Parameter);
            voice->setFilterSwitch(filter2SwitchParameter);
            
            voice->updateVoice(lastSampleRate);
            
            voice->setIndex(i + 20);
        }
    }
}

void S1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool S1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void S1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto attack1Parameter = treeState.getRawParameterValue(ADSR_1_ATTACK_ID);
    auto decay1Parameter = treeState.getRawParameterValue(ADSR_1_DECAY_ID);
    auto sustain1Parameter = treeState.getRawParameterValue(ADSR_1_SUSTAIN_ID);
    auto release1Parameter = treeState.getRawParameterValue(ADSR_1_RELEASE_ID);
    auto waveType1Parameter = treeState.getRawParameterValue(WAVE_TYPE_1_ID);
    auto level1Parameter = treeState.getRawParameterValue(LEVEL_1_ID);
    auto drive1Parameter = treeState.getRawParameterValue(DISTORTION_1_DRIVE_ID);
    //auto range1Parameter = treeState.getRawParameterValue(DISTORTION_1_RANGE_ID);
    auto blend1Parameter = treeState.getRawParameterValue(DISTORTION_1_BLEND_ID);
    //auto volume1Parameter = treeState.getRawParameterValue(DISTORTION_1_VOLUME_ID);
    auto distortion1SwitchParameter = treeState.getRawParameterValue(DISTORTION_1_SWITCH_ID);
    
    auto attack2Parameter = treeState.getRawParameterValue(ADSR_2_ATTACK_ID);
    auto decay2Parameter = treeState.getRawParameterValue(ADSR_2_DECAY_ID);
    auto sustain2Parameter = treeState.getRawParameterValue(ADSR_2_SUSTAIN_ID);
    auto release2Parameter = treeState.getRawParameterValue(ADSR_2_RELEASE_ID);
    auto waveType2Parameter = treeState.getRawParameterValue(WAVE_TYPE_2_ID);
    auto level2Parameter = treeState.getRawParameterValue(LEVEL_2_ID);
    auto drive2Parameter = treeState.getRawParameterValue(DISTORTION_2_DRIVE_ID);
    //auto range2Parameter = treeState.getRawParameterValue(DISTORTION_2_RANGE_ID);
    auto blend2Parameter = treeState.getRawParameterValue(DISTORTION_2_BLEND_ID);
    //auto volume2Parameter = treeState.getRawParameterValue(DISTORTION_2_VOLUME_ID);
    auto distortion2SwitchParameter = treeState.getRawParameterValue(DISTORTION_2_SWITCH_ID);
    
    auto filterCutOffFrequency1Parameter = treeState.getRawParameterValue(FILTER_1_CUTOFF_ID);
    auto filterCutOffFrequency2Parameter = treeState.getRawParameterValue(FILTER_2_CUTOFF_ID);
    
    auto filterAttack1Parameter = treeState.getRawParameterValue(FILTER_1_ATTACK_ID);
    auto filterAttack2Parameter = treeState.getRawParameterValue(FILTER_2_ATTACK_ID);
    
    filter1SwitchParameter = treeState.getRawParameterValue(FILTER_1_SWITCH_ID);
    filter2SwitchParameter = treeState.getRawParameterValue(FILTER_2_SWITCH_ID);
    
    for(int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {
            
            //myVoice->setSampleRate(lastSampleRate);
            //myVoice->setBufferSize(buffer.getNumSamples());
            //myVoice->setNumChannels(buffer.getNumChannels());

            myVoice->setWaveType(waveType1Parameter);
            myVoice->setLevel(level1Parameter);
            
            myVoice->setDrive(drive1Parameter);
            //myVoice->setRange(range1Parameter);
            myVoice->setBlend(blend1Parameter);
            //myVoice->setVolume(volume1Parameter);
            
            myVoice->setSwitch(distortion1SwitchParameter);
            myVoice->setCutOff(filterCutOffFrequency1Parameter);
            
            adsrParameters.attack = float(*attack1Parameter);
            adsrParameters.decay = float(*decay1Parameter);
            adsrParameters.sustain = float(*sustain1Parameter);
            adsrParameters.release = float(*release1Parameter);
            
            myVoice->setAdsrParameters(adsrParameters);
            
            filterADSRparameters.attack = float(*filterAttack1Parameter);
            filterADSRparameters.decay = 0.1f;
            filterADSRparameters.sustain = 1;
            filterADSRparameters.release = 3000;
            
            myVoice->setFilterADSRParameters(filterADSRparameters);
            
            myVoice->setADSRFilterSwitch(filter1SwitchParameter);
            
            myVoice->setFilterType(filter1Type);
            myVoice->setFilterRes(filterResDial1Parameter);
            
            myVoice->setFilterSwitch(filter1SwitchParameter);
        }
    }
    
    for(int i = 0; i < mySynth2.getNumVoices(); i++)
    {
        if((myVoice = dynamic_cast<SynthVoice*>(mySynth2.getVoice(i)))) {
            
            //myVoice->setSampleRate(lastSampleRate);
            //myVoice->setBufferSize(buffer.getNumSamples());
            //myVoice->setNumChannels(buffer.getNumChannels());

            myVoice->setWaveType(waveType2Parameter);
            myVoice->setLevel(level2Parameter);
            
            myVoice->setDrive(drive2Parameter);
            //myVoice->setRange(range2Parameter);
            myVoice->setBlend(blend2Parameter);
            //myVoice->setVolume(volume2Parameter);
            
            myVoice->setSwitch(distortion2SwitchParameter);
            
            myVoice->setCutOff(filterCutOffFrequency2Parameter);
            
            adsrParameters.attack = float(*attack2Parameter);
            adsrParameters.decay = float(*decay2Parameter);
            adsrParameters.sustain = float(*sustain2Parameter);
            adsrParameters.release = float(*release2Parameter);
            
            myVoice->setAdsrParameters(adsrParameters);
            
            filterADSRparameters.attack = float(*filterAttack2Parameter);
            filterADSRparameters.decay = 0.1f;
            filterADSRparameters.sustain = 1;
            filterADSRparameters.release = 3000;
            
            myVoice->setFilterADSRParameters(filterADSRparameters);
            
            myVoice->setADSRFilterSwitch(filter2SwitchParameter);
            
            myVoice->setFilterType(filter2Type);
            myVoice->setFilterRes(filterResDial2Parameter);
            
            myVoice->setFilterSwitch(filter2SwitchParameter);
        }
    }
    
    buffer.clear();
     
    updateFilter();
    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> block (buffer);
    
    juce::AudioBuffer< float > buffer2;
    buffer2.setSize(buffer.getNumChannels(), buffer.getNumSamples());
    buffer2.clear();
    
    mySynth2.renderNextBlock(buffer2, midiMessages, 0, buffer2.getNumSamples());
    
    juce::dsp::AudioBlock<float> block2 (buffer2);
    
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        for(int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            buffer.addSample(channel, sample, buffer2.getSample(channel, sample));
        }
    }
    /*
    params.roomSize   = 100.0f;//*apvts.getRawParameterValue ("Room Size");
    params.damping    = 100.0f;//*apvts.getRawParameterValue ("Damping");
    params.width      = 100.0f;//*apvts.getRawParameterValue ("Width");
    params.wetLevel   = 100.0f;//*apvts.getRawParameterValue ("Dry/Wet");
    params.dryLevel   = 1.0f;//1.0f - *apvts.getRawParameterValue ("Dry/Wet");
    params.freezeMode = 1.0f;//*apvts.getRawParameterValue ("Freeze");
    
    leftReverb.setParameters (params);
    rightReverb.setParameters (params);

    juce::dsp::AudioBlock<float> block3 (buffer);
        
    auto leftBlock = block3.getSingleChannelBlock (0);
    auto rightBlock = block3.getSingleChannelBlock (1);
    
    juce::dsp::ProcessContextReplacing<float> leftContext (leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext (rightBlock);
    
    leftReverb.process (leftContext);
    rightReverb.process (rightContext);*/
    
    buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    buffer.getRMSLevel(1, 0, buffer.getNumSamples());
}

//==============================================================================
bool S1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* S1AudioProcessor::createEditor()
{
    return new S1AudioProcessorEditor (*this);
}

//==============================================================================
void S1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    juce::XmlElement* childToReplace = xml->getChildByAttribute("id", CURRENT_PRESET_COMPOSED_NAME);
    xml->removeChildElement(childToReplace, true);
    childToReplace = xml->getChildByAttribute("id", "*");
    
    //TODO: Maybe it is a duplicate code lines...
    xml->removeChildElement(childToReplace, true);
    childToReplace = xml->getChildByAttribute("ID", "*");
    xml->removeChildElement(childToReplace, true);
    
    juce::XmlElement* newChilElement = new juce::XmlElement("PARAM");
    newChilElement->setAttribute("id", CURRENT_PRESET_COMPOSED_NAME);
    newChilElement->setAttribute("value", currentPresetComposedName);
    xml->addChildElement(newChilElement);
    copyXmlToBinary (*xml, destData);
}

void S1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
 
    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName (treeState.state.getType())) {
            juce::ValueTree valueTree = juce::ValueTree::fromXml (*xmlState);
            
            currentPresetComposedName = valueTree.getChildWithProperty("id", CURRENT_PRESET_COMPOSED_NAME).getProperty("value").
            toString().toStdString();
            
            DBG(currentPresetComposedName);
            
            if(currentPresetComposedName == "") {
                currentPresetComposedName = utilities.buildPresetComposedName(COMMON_APPLICATION_DATA_DIRECTORY_INDEX, DEFAULT_PRESET_INIT_NAME, DEFAULT_PRESET_INIT_NAME) ;
            }
            
            DBG(currentPresetComposedName);
            
            if (!(presetsMap.find(currentPresetComposedName) != presetsMap.end())) {
                currentPresetComposedName = utilities.buildPresetComposedName(COMMON_APPLICATION_DATA_DIRECTORY_INDEX, DEFAULT_PRESET_INIT_NAME, DEFAULT_PRESET_INIT_NAME) ;
            }
            
            DBG(currentPresetComposedName);
            
            treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
        }
    }
}

std::string S1AudioProcessor::movePresets (int direction)
{
    if(direction == 0
       || presetsMap.size() == 1) {
        return currentPresetComposedName;
    }
    std::map<juce::String, juce::var>::iterator currentPresetIterator = presetsMap.find(currentPresetComposedName);
    
    if(direction > 0) {
        std::cout << currentPresetComposedName << std::endl;
        currentPresetIterator++;
        std::cout << presetsMap.size() << std::endl;
    }
    else {
        if(currentPresetIterator == presetsMap.begin()) {
            currentPresetIterator = presetsMap.end();
        }
        currentPresetIterator--;
        
    }
    
    if (currentPresetIterator == presetsMap.end()) {
        currentPresetIterator = presetsMap.begin();
    }
    
    currentPresetComposedName = currentPresetIterator->first.toStdString();
    
    juce::var jsonToLoad = currentPresetIterator->second;
    
    this->loadSettingsFromPresetJSON(jsonToLoad);
    
    return currentPresetComposedName;
}

void S1AudioProcessor::loadSettingsFromPresetJSON(juce::var jsonToLoad) {
    juce::var drv;
    juce::var presetSettings = jsonToLoad.getProperty("settings", drv);
    juce::Array<juce::var>* presetSettingsArray = presetSettings.getArray();
    
    //std::cout << "isObject " << presetSettings.isObject() << std::endl;
    
    //std::cout << "isArray " << presetSettings.isArray() << std::endl;
    
    std::map<std::string,std::map<std::string,std::string>> PARAMETERS_GLOBAL_MAP = constants->getParametersGlobalMap();
    
    for(auto parametersGlobalMapIt = PARAMETERS_GLOBAL_MAP.cbegin(); parametersGlobalMapIt != PARAMETERS_GLOBAL_MAP.cend(); ++parametersGlobalMapIt)
    {
        juce::var presetParameter = stof(PARAMETERS_GLOBAL_MAP[parametersGlobalMapIt->first]["DEFAULT"]);
        if(presetSettings.hasProperty(juce::Identifier(parametersGlobalMapIt->first))) {
            presetParameter = presetSettings.getProperty(juce::Identifier(parametersGlobalMapIt->first), drv);
        }
        
        treeState.state.getChildWithProperty("id", juce::String(parametersGlobalMapIt->first)).setProperty("value", presetParameter, treeState.undoManager);
        
        treeState.replaceState(treeState.state);
    }
}

std::string S1AudioProcessor::buildPresetJSON(std::string newPresetName,
                                                             std::string newPresetFolderName,
                                                             std::string newPresetCreatorName,
                                                             bool loadDefault) {
    
    std::string newPresetJsonTemplate = PRESET_JSON_TEMPLATE;
    
    utilities.replace(newPresetJsonTemplate, "CREATOR_PLACEHOLDER", newPresetCreatorName);
    utilities.replace(newPresetJsonTemplate, "CREATOR_PLACEHOLDER", newPresetCreatorName);
    utilities.replace(newPresetJsonTemplate, "FOLDER_PLACEHOLDER", newPresetFolderName);
    utilities.replace(newPresetJsonTemplate, "PRESET_NAME_PLACEHOLDER", newPresetName);
    
    std::string jsonSettings = "{";
    
    std::map<std::string,std::map<std::string,std::string>> PARAMETERS_GLOBAL_MAP = constants->getParametersGlobalMap();
    
    for(auto parametersGlobalMapIt = PARAMETERS_GLOBAL_MAP.cbegin(); parametersGlobalMapIt != PARAMETERS_GLOBAL_MAP.cend(); ++parametersGlobalMapIt)
    {
        juce::var parameterValue = stof(PARAMETERS_GLOBAL_MAP[parametersGlobalMapIt->first]["DEFAULT"]);
        
        if(!loadDefault) {
            parameterValue = treeState.state.getChildWithProperty("id", juce::String(parametersGlobalMapIt->first)).getProperty("value");
        }
        
        jsonSettings = jsonSettings.append("\"").append(parametersGlobalMapIt->first).append("\": \"").append(parameterValue.toString().toStdString()).append("\",");
         
    }
    
    jsonSettings = jsonSettings.substr(0, jsonSettings.size()-1);
    
    jsonSettings = jsonSettings.append("}");
    
    utilities.replace(newPresetJsonTemplate, "SETTINGS_PLACEHOLDER", jsonSettings);
    
    return newPresetJsonTemplate;
}

void S1AudioProcessor::loadSettingsFromPresetComposedName(std::string presetComposedName) {
    std::map<juce::String, juce::var>::iterator currentPresetIterator = presetsMap.find(presetComposedName);
    
    currentPresetComposedName = presetComposedName;
    
    juce::var jsonToLoad = currentPresetIterator->second;
    
    this->loadSettingsFromPresetJSON(jsonToLoad);
    
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->changeProgramSelectorName(currentPresetComposedName);
}

inline bool S1AudioProcessor::ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void S1AudioProcessor::showPresetsBrowser() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->showPresetsBrowser();
    return;
}

void S1AudioProcessor::hidePresetsBrowser() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->hidePresetsBrowser();
    return;
}

void S1AudioProcessor::showPresetSave() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->showPresetSave();
    return;
}

void S1AudioProcessor::aaa() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->aaa();
    return;
}

void S1AudioProcessor::hidePresetSave() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->hidePresetSave();
    return;
}

std::map<juce::String, juce::var> S1AudioProcessor::getPresetsMap() {
    return presetsMap;
}

void S1AudioProcessor::selectPresetFolder(std::string folderName) {
    std::cout << folderName << std::endl;
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->selectPresetFolder(folderName);
    return;
}

void S1AudioProcessor::selectSavePresetFolder(std::string folderName) {
    std::cout << folderName << std::endl;
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->selectSavePresetFolder(folderName);
    return;
}

void S1AudioProcessor::refreshFoldersAndPresets() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->refreshFoldersAndPresets();
    return;
}

void S1AudioProcessor::resetLayers() {
    S1AudioProcessorEditor* pluginEditor = (S1AudioProcessorEditor*)getActiveEditor();
    pluginEditor->resetLayers();
    return;
}

std::string S1AudioProcessor::getCurrentPresetComposedName() {
    return currentPresetComposedName;
}

void S1AudioProcessor::installPresets() {
    std::string newFolderNameValue = "AEW";
    std::string presetNameValue = "AEW";
    std::string presetCreatorNameValue = "AEW";
    utilities.createNewPresetFolder(newFolderNameValue);
    std::string newPresetJson = this->buildPresetJSON(presetNameValue, newFolderNameValue, presetCreatorNameValue);
    utilities.writeNewPresetFile(presetNameValue, newFolderNameValue, presetCreatorNameValue, newPresetJson);
}

void S1AudioProcessor::updatePresetsMap() {
    
    constants = new Constants();
    
    juce::File commonPresetsFolder (juce::File (juce::File::getSpecialLocation (juce::File::commonApplicationDataDirectory))
                              .getChildFile (PRESETS_PATH));
    
    juce::File userPresetsFolder (juce::File (juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory))
                                  .getChildFile (PRESETS_PATH));
    
    juce::String x = commonPresetsFolder.getFullPathName();
    juce::String y = userPresetsFolder.getFullPathName();
    
    presetsMap = insertInitPresetMap(presetsMap);
    presetsMap = iterateFolderAndInsertPresetMap(commonPresetsFolder, presetsMap, utilities, COMMON_APPLICATION_DATA_DIRECTORY_INDEX);
    presetsMap = iterateFolderAndInsertPresetMap(userPresetsFolder, presetsMap, utilities, USER_APPLICATION_DATA_DIRECTORY_INDEX);
    
}

std::map<juce::String, juce::var> S1AudioProcessor::insertInitPresetMap(std::map<juce::String, juce::var> map) {
    std::string patchIndex = presetsUtilities.buildInitPresetComposedName();
    //utilities.buildPresetComposedName(COMMON_APPLICATION_DATA_DIRECTORY_INDEX, DEFAULT_PRESET_INIT_NAME, DEFAULT_PRESET_INIT_NAME);
    
    map.insert(std::pair<juce::String, juce::var>(patchIndex, buildPresetJSON(DEFAULT_PRESET_INIT_NAME, DEFAULT_PRESET_INIT_NAME, DEFAULT_CURRENT_PRESET_CREATOR_NAME, true)));
    
    return map;
}

std::map<juce::String, juce::var> S1AudioProcessor::iterateFolderAndInsertPresetMap(juce::File folder,
                                     std::map<juce::String, juce::var> map,
                                     Utilities utilities,
                                     std::string folderIndex) {
    
    juce::String patchIndex = "";
    
    for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator (folder, false, "*", juce::File::findFilesAndDirectories)) {
        
        entry.isDirectory();
        std::string folderName = entry.getFile().getFileName().toStdString();
        
        if(entry.isDirectory()) {
            for (juce::DirectoryEntry entryF : juce::RangedDirectoryIterator (entry.getFile(), false, "*", juce::File::findFilesAndDirectories)) {
                
                juce::File f = entryF.getFile();
                
                if( !ends_with(f.getFileName().toStdString(), PRESET_FILE_EXTENSION)) {
                    
                    continue;
                }
                
                auto fileText = f.loadFileAsString();

                juce::var json = juce::JSON::parse(f);
                
                if(json.isVoid() || !json.hasProperty("preset_name")) {
                    continue;
                }
                
                juce::var drv;
                juce::var synth_version = json.getProperty("synth_version", drv);
                
                juce::var preset_name = json.getProperty("preset_name", drv);
                
                patchIndex = utilities.buildPresetComposedName(folderIndex, folderName, preset_name.toString().toStdString());
                map.insert(std::pair<juce::String, juce::var>(patchIndex, json));
            }
        }
    }
    
    map = utilities.sortMapStringAndString(map);
    
    return map;
}

void S1AudioProcessor::updateFilter ()
{
    filter1SwitchParameter = treeState.getRawParameterValue(FILTER_1_SWITCH_ID);
    filter2SwitchParameter = treeState.getRawParameterValue(FILTER_2_SWITCH_ID);
    
    //auto filterCutoffDial1Parameter = treeState.getRawParameterValue(FILTER_CUTOFF_DIAL_ID_1);
    filterResDial1Parameter = treeState.getRawParameterValue(FILTER_1_RES_ID);
    auto filterMenu1Parameter = treeState.getRawParameterValue(FILTER_1_TYPE_ID);
    
    //auto filterCutoffDial2Parameter = treeState.getRawParameterValue(FILTER_CUTOFF_DIAL_ID_2);
    filterResDial2Parameter = treeState.getRawParameterValue(FILTER_2_RES_ID);
    auto filterMenu2Parameter = treeState.getRawParameterValue(FILTER_2_TYPE_ID);
    
    if (float(*filterMenu1Parameter) == 0)
    {
        filter1Type = juce::dsp::StateVariableTPTFilterType::lowpass;
    }
    
    if (float(*filterMenu1Parameter) == 1)
    {
        filter1Type = juce::dsp::StateVariableTPTFilterType::highpass;
    }
    
    if (float(*filterMenu1Parameter) == 2)
    {
        filter1Type = juce::dsp::StateVariableTPTFilterType::bandpass;
    }
    
    if (float(*filterMenu2Parameter) == 0)
    {
        filter2Type = juce::dsp::StateVariableTPTFilterType::lowpass;
    }
    
    if (float(*filterMenu2Parameter) == 1)
    {
        filter2Type = juce::dsp::StateVariableTPTFilterType::highpass;
    }
    
    if (float(*filterMenu2Parameter) == 2)
    {
        filter2Type = juce::dsp::StateVariableTPTFilterType::bandpass;
    }
    
    DBG(float(*filterMenu1Parameter));
    DBG(float(*filterMenu2Parameter));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new S1AudioProcessor();
}
