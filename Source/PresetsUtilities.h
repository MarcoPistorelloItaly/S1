/*
  ==============================================================================

    Preset.h
    Created: 18 Feb 2025 8:59:53pm
    Author:  Marco

  ==============================================================================
*/

#pragma once

#include "Constants.h"
#include "Utilities.h"

class PresetsUtilities
{
    public:
        PresetsUtilities()
        {
        }
        
        std::string buildInitPresetComposedName()
        {
            return utilities.buildPresetComposedName(COMMON_APPLICATION_DATA_DIRECTORY_INDEX, DEFAULT_PRESET_INIT_NAME, DEFAULT_PRESET_INIT_NAME);
        }
    
    private:
        Utilities utilities;
    
};
