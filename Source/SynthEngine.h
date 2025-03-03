/*
  ==============================================================================

    SynthEngine.h
    Created: 4 Jan 2025 2:58:59pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Adsr.h"
#include "Distortion.h"
#include "Filter.h"
#include "Oscillator.h"

//==============================================================================
/*
*/
class SynthEngine    : public juce::Component
{
public:
    SynthEngine(S1AudioProcessor&, int);
    ~SynthEngine();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    S1AudioProcessor& processor;
    Oscillator oscillator;
    Adsr adsr;
    Distortion distortion;
    Filter filter;
    
    int indexParam;
    
public:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthEngine)
};
