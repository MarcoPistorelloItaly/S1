/*
  ==============================================================================

    SynthSound.h
    Created: 9 Feb 2025 5:43:35pm
    Author:  Marco

  ==============================================================================
*/

#pragma once
#include <../JuceLibraryCode/JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int)
    {
        return true;
    }
 
    bool appliesToChannel (int)
    {
        return true;
    }
};
