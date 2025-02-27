/*
  ==============================================================================

    SynthVoice.h
    Created: 9 Feb 2025 5:41:47pm
    Author:  Marco

  ==============================================================================
*/

#pragma once
#include <../JuceLibraryCode/JuceHeader.h>
#include "SynthSound.h"
#include "Constants.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    SynthVoice()
    {
    }
    
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void setWaveType(std::atomic<float>* waveTypeParam)
    {
        waveType = float(*waveTypeParam);
    }
    
    void setDrive(std::atomic<float>* drive)
    {
        driveParameter = drive;
    }
    void setBlend(std::atomic<float>* blend)
    {
        blendParameter = blend;
    }
    
    void setLevel(std::atomic<float>* levelParam)
    {
        level = float(*levelParam);
    }
    void setSwitch(std::atomic<float>* switchParam)
    {
        switchParameter = switchParam;
    }
    void setSampleRate(float sampleRateParam) {
        sampleRate = sampleRateParam;
    }
    void setCutOff(std::atomic<float>*  cutOffFrequency) {
        filterCutOffFrequency = cutOffFrequency;
    }
    void setAdsrParameters(juce::ADSR::Parameters adsrParametersParam)
    {
        adsrParameters = adsrParametersParam;
    }
    void setFilterADSRParameters(juce::ADSR::Parameters filterADSRParametersParam)
    {
        filterADSRParameters = filterADSRParametersParam;
    }
    void setADSRFilterSwitch(std::atomic<float>*   ADSRSwitchParam)
    {
        ADSRFilterSwitchValue = float(*ADSRSwitchParam);
    }
    void setNumChannels(int numChannelsParam)
    {
        numChannels = numChannelsParam;
    }
    void setFilterType(juce::dsp::StateVariableTPTFilterType newType) {
        filter.setType(newType);
    }
    
    void setFilterRes(std::atomic<float>* newResonance) {
        filter.setResonance(float(*newResonance));
    }
    
    void setBufferSize(float bufferSizeParam) {
        bufferSize = bufferSizeParam;
    }
    void setFilterSwitch(std::atomic<float>*  newValue) {
        filterSwitch = float(*newValue);
    }
    
    void setIndex(int indexParam) {
        index = indexParam;
    }
    
    void updateVoice(float sampleRateParam) {
        sampleRate = sampleRateParam;
        samplePeriod = 1 / sampleRate;
        newCutSmoothed.reset(sampleRate, 0.5);
        
        adsr.setSampleRate(sampleRate);
        filterADSR.setSampleRate(sampleRate);
        
        adsr.reset();
        filterADSR.reset();
    }
    
    /*A sawtooth wave could be calculated like this:
     
     value = x - floor(x);
     A triangle could be calculated like this:

     value = 1.0 - fabs(fmod(x,2.0) - 1.0);*/
    
    double getWaveformBetweenMinusOneToPlusOne(int chosenWavetype)
    {
        
        double value;
        double mPhase = fmod(timeFromAttack * 2.0 * juce::MathConstants<double>::pi * frequencyOfThisNote, 2.0 * juce::MathConstants<double>::pi);
        
        double t = mPhase / twoPI;
        
        switch (chosenWavetype) {
            case 0://OSCILLATOR_MODE_SINE:
                value = sin(mPhase);
                break;
            case 1://OSCILLATOR_MODE_SAW:
                value = ((2.0 * (mPhase / (2.0 * juce::MathConstants<double>::pi))) - 1.0);
                
                value -= poly_blep(t);
                
                break;
            case 2://OSCILLATOR_MODE_SQUARE:
                if (mPhase < juce::MathConstants<double>::pi) {
                    value = 1.0;
                } else {
                    value = -1.0;
                }
                
                value += poly_blep(t);
                value -= poly_blep(fmod(t + 0.5, 1.0));
                
                break;
            case 3://OSCILLATOR_MODE_TRIANGLE:
                /*value = -1.0 + (2.0 * mPhase / twoPI);
                value = 2.0 * (fabs(value) - 0.5);*/
                
                if (mPhase < juce::MathConstants<double>::pi) {
                    value = 1.0;
                } else {
                    value = -1.0;
                }
                
                value += poly_blep(t);
                value -= poly_blep(fmod(t + 0.5, 1.0));
                
                
                value = mPhaseIncrement * value + (1 - mPhaseIncrement) * lastOutput;
                lastOutput = value;
                
                break;
            default:
                break;
        }
        return value;
    }
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        playedMidiNoteNumber = midiNoteNumber;
        voiceVelocity = velocity;
        frequencyOfThisNote = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber, 440 /*XXXXXXXXX*/);
        isReleased = false;
        timeFromRelease = 0;
        adsr.noteOn();
        filterADSR.noteOn();
    }
    
    void stopNote (float velocity, bool allowTailOff)
    {
        allowTailOff = true;
        timeFromRelease = 0;
        adsr.noteOff();
        filterADSR.noteOff();
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        if(!isVoiceActive()) {
            return;
        }
        
        adsr.setParameters(adsrParameters);
        
        filterADSR.setParameters(filterADSRParameters);
        
        mPhaseIncrement = (frequencyOfThisNote * 2 * juce::MathConstants<double>::pi) / sampleRate;
        
        float driverParameterBasedOnMidiNoteNumber = calculateDriverParameterBasedOnMidiNoteNumber();
    
        for(int sample = 0; sample < numSamples; ++sample)
        {
            newCut = float(*filterCutOffFrequency) * filterADSR.getNextSample();
            
            if(newCut < 20) {
                newCut = 20;
            }
            if(newCut > 20000) {
                newCut = 20000;
            }
            filter.setCutoffFrequency(newCut);
            
            double sampleCalculatedValue = getWaveformBetweenMinusOneToPlusOne(waveType) * voiceVelocity;
            
            if(float(*switchParameter) == 1) {
                sampleCalculatedValue = distortSample(sampleCalculatedValue,
                                                      blendParameter,
                                                      driverParameterBasedOnMidiNoteNumber);
            }
            
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                nextSampleAfterFiltering = sampleCalculatedValue;
                if(filterSwitch == 1) {
                    nextSampleAfterFiltering = filter.processSample(channel, sampleCalculatedValue);
                }
                
                nextSampleAfterFiltering = nextSampleAfterFiltering * adsr.getNextSample() * level;
                
                outputBuffer.addSample(channel, startSample, nextSampleAfterFiltering);
            }
            
            if(isPlayingButReleased()) {
                timeFromRelease = timeFromRelease + samplePeriod;
                if(timeFromRelease > adsr.getParameters().release) {
                    
                    clearCurrentNote();
                    timeFromAttack = 0;
                    
                    filterADSR.reset();
                }
            }
            
            timeFromAttack = timeFromAttack + samplePeriod;
            
            ++startSample;
        }
        
    }
    
    float calculateDriverParameterBasedOnMidiNoteNumber() {
        int diffUp96 = playedMidiNoteNumber - 96;
        if(diffUp96 < 0) {
            diffUp96 = 0;
        }
        
        int diffUp127 = 127 - 96;
                            
        float driveParameterFloat = float(*driveParameter);
        
        float driveParameterReduce = (driveParameterFloat) * diffUp96 / diffUp127;
        
        if(driveParameterReduce > 1) {
            driveParameterReduce = 1;
        }
        if(driveParameterReduce < 0) {
            driveParameterReduce = 0;
        }
        
        driveParameterReduce = driveParameterReduce *
            (constants.getParamValue(DISTORTION_1_DRIVE_ID, "MAX") - constants.getParamValue(DISTORTION_1_DRIVE_ID, "MIN"));
        
        driveParameterFloat = driveParameterFloat - driveParameterReduce;
        
        return driveParameterFloat;
    }
    
    float distortSample(float cleanSample,
                        std::atomic<float>* blendParameter,
                        float driveParameterFloat) {
        float distortedSample = (2.f / juce::float_Pi) * atan(cleanSample * driveParameterFloat * 1);
        float newSample = ((distortedSample * float(*blendParameter) ) + (cleanSample * (1.f - float(*blendParameter))));
        return newSample;
    }
    
    double poly_blep(double t)
    {
        double dt = mPhaseIncrement / twoPI;
        // 0 <= t < 1
        if (t < dt) {
            t /= dt;
            return t+t - t*t - 1.0;
        }
        // -1 < t < 0
        else if (t > 1.0 - dt) {
            t = (t - 1.0) / dt;
            return t*t + t+t + 1.0;
        }
        // 0 otherwise
        else return 0.0;
    }
    
    void prepareFilter() {
        filter.reset();
        filterSpecs.maximumBlockSize = bufferSize;
        filterSpecs.sampleRate = sampleRate;
        filterSpecs.numChannels = numChannels;
        filter.prepare(filterSpecs);
        filter.snapToZero();
    }
    
    
    
private:
    
    double level;
    double frequencyOfThisNote = 0;
    double timeFromAttack;
    double timeFromRelease;
    double const twoPI = 2.0 * juce::MathConstants<double>::pi;
    double mPhaseIncrement;
    double lastOutput = 0.0;
    double newCut;
    double newCutTarget;
    
    bool isReleased = false;
    
    int waveType;
    
    std::atomic<float>* driveParameter;
    std::atomic<float>* blendParameter;
    std::atomic<float>* switchParameter;
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
    
    juce::ADSR filterADSR;
    juce::ADSR::Parameters filterADSRParameters;
    
    int filterSwitch;
    int ADSRFilterSwitchValue;
    
    double sampleRate;
    
    float filterFreq;
    float filterRes;
    float bufferSize;
    
    std::atomic<float>* filterCutOffFrequency;
    
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> newCutSmoothed = juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>();
    
    juce::dsp::StateVariableTPTFilter<float> filter;
    
    float nextSampleAfterFiltering = 0;
    
    int numChannels;
    
    juce::dsp::ProcessSpec filterSpecs;
    
    double samplePeriod;
    
    int index;
    
    float voiceVelocity;
    
    int playedMidiNoteNumber;
    
    Constants constants;
    
public:
    
};


