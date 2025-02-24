/*
  ==============================================================================

    Utilities.h
    Created: 31 Dec 2024 11:40:03am
    Author:  Marco

  ==============================================================================
*/

#pragma once

//#include "PluginProcessor.h"
#include "Constants.h"

#define COLOUR_1_1 148
#define COLOUR_1_2 0
#define COLOUR_1_3 211

#define COLOUR_2_1 75
#define COLOUR_2_2 0
#define COLOUR_2_3 130

#define COLOUR_3_1 0
#define COLOUR_3_2 0
#define COLOUR_3_3 255

#define COLOUR_4_1 0
#define COLOUR_4_2 255
#define COLOUR_4_3 0

#define COLOUR_5_1 255
#define COLOUR_5_2 255
#define COLOUR_5_3 0

#define COLOUR_6_1 255
#define COLOUR_6_2 127
#define COLOUR_6_3 0

#define COLOUR_7_1 255
#define COLOUR_7_2 0
#define COLOUR_7_3 0

#define COLOUR_8_1 255
#define COLOUR_8_2 0
#define COLOUR_8_3 0

#define COLOUR_GREEN_1 52
#define COLOUR_GREEN_2 175
#define COLOUR_GREEN_3 41

#define COLOUR_YELLOW_1 200
#define COLOUR_YELLOW_2 175
#define COLOUR_YELLOW_3 41

#define COLOUR_ORANGE_1 255
#define COLOUR_ORANGE_2 0
#define COLOUR_ORANGE_3 0

#define COLOUR_RED_1 255
#define COLOUR_RED_2 0
#define COLOUR_RED_3 0

#define COLOUR_BLACK_1 0
#define COLOUR_BLACK_2 0
#define COLOUR_BLACK_3 0

#define ABSOLUTE_PATH_PRESETS_MAC_OSX "/Library/Audio/Presets/"
#define PRESET_FILE_EXTENSIONE "s1preset"
#define PLUGIN_MAIN_FOLDER "MarcoPysto"
#define S1_PRESETS_FOLDER "S1"

class Utilities
{
public:
    Utilities()
    {
    }

    juce::Colour renderColor(float valueToRender, float min, float max, int colours[8][3])
    {
        
        
        if(valueToRender < min) {
            valueToRender = min;
        }
        if(valueToRender > max) {
            valueToRender = max;
        }
        
        //std::cout << "max   " << max << std::endl;
        
        max = max - min;
        valueToRender = valueToRender - min;
        min = 0;
        
        //std::cout << "valueToRenderb   " << valueToRender << std::endl;
        
        float steps = 7;
        
        float max2 = 0;
        float min2 = 0;
        float valueToRender2 = 0;
        int stepToChoose = 0;
        for (int i = 0; i < steps; i++) {
            
            double iOnSteps = (i/steps);
            double stepValueMax = (max * iOnSteps);
            
           // std::cout << "iOnSteps" << i << "   " << iOnSteps << std::endl;
            //std::cout << "stepValueMax" << i << "   " << stepValueMax << std::endl;
        
            
            if(valueToRender >= stepValueMax) {
                
                float step0 = (i/steps);
                float step1 = ((i + 1)/steps);
                
                min2 = (max * step0);
                max2 = (max * step1);
                stepToChoose = i;
            }
        }
        
        max2 = max2 - min2;
        if(max2 > max) {
            max2 = max;
        }
        
        //std::cout << "min2   " << min2 << std::endl;
        valueToRender2 = valueToRender - min2;
        float proportion = valueToRender2 / max2;
        
        float colourRGB1 = colours[stepToChoose][0] * (1 - proportion) + colours[stepToChoose + 1][0] * (proportion);
        float colourRGB2 = colours[stepToChoose][1] * (1 - proportion) + colours[stepToChoose + 1][1] * (proportion);
        float colourRGB3 = colours[stepToChoose][2] * (1 - proportion) + colours[stepToChoose + 1][2] * (proportion);
        
        /*
        std::cout << "Proportion " << proportion << std::endl;;
        std::cout << "valueToRender2   " << valueToRender2 << std::endl;
        std::cout << "max2   " << max2 << std::endl;
        std::cout << "stepToChoose   " << stepToChoose << std::endl;
        */
        
        //std::cout << "colourRGB1   " << colourRGB1 << std::endl;
        //if(colourRGB1 < 0) {
            //std::cout << "colourRGB1P " << proportion << std::endl;;
        //}
        
        //std::cout << "RESULT    " << colourRGB1 << "  " << colourRGB2 << "  " << colourRGB3 << std::endl;
        
        std::to_string(42);
        
        //string result = std::to_string(colourRGB1) + " " + std::to_string(colourRGB2) + " " + std::to_string(colourRGB3);
        
        juce::Colour colour1;
        colour1 = colour1.fromRGB(colourRGB1, colourRGB2, colourRGB3);
        
        return colour1;
    }
    
    void drawBlur(juce::Graphics& g, juce::Line<float> line, juce::Colour colour, float overlays[20][2]) {
        g.setColour (colour);
        for(int i = 0; i < sizeof(overlays); i++) {
            if(overlays[i][0] > 0 && overlays[i][1] > 0) {
                g.setOpacity(overlays[i][1]);
                g.drawLine (line, overlays[i][0]);
            }
            
        }
    }
    
    std::map<juce::String, juce::var> sortMapStringAndString(std::map<juce::String, juce::var> map) {
        std::vector<std::pair<juce::String, juce::var>> vec;
         
        // copy key-value pairs from the map to the vector
        std::copy(map.begin(),
                map.end(),
                std::back_inserter<std::vector<std::pair<juce::String, juce::var>>>(vec));
     
        // sort the vector by increasing the order of its pair's second value
        // if the second value is equal, order by the pair's first value
        std::sort(vec.begin(), vec.end(),
                [](const std::pair<juce::String, juce::var> &l, const std::pair<juce::String, juce::var> &r)
                {
                    /*
                    if (l.second != r.second) {
                        return l.second < r.second;
                    }*/
     
                    return l.first < r.first;
                });
     
        // print the vector
        //for (auto const &pair: vec) {
          //  std::cout << '{' << pair.first << "," << '}' << std::endl;
        //}
        
        return map;
    }
    
    juce::StringArray explode(juce::String myString, juce::String stringSeparator)
    {
        juce::StringArray tokens;
        tokens.addTokens (myString, stringSeparator, "");

        /*
        for (int i=0; i<tokens.size(); i++)
        {
            if(tokens[i] == "") {
                tokens.remove(i);
            } // holds next token
            
        }*/
        
        return tokens;
    }
    
    juce::String buildPatchNameFromStringArray(juce::StringArray currentPresetComposedNameComps) {
        
//        std::cout << "s0 size " << currentPresetComposedNameComps.size() << std::endl;
        
        std::string result = currentPresetComposedNameComps[6].toStdString();
        
//        std::cout << "s0 " << currentPresetComposedNameComps[0].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[1].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[2].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[3].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[4].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[5].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[6].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[7].toStdString() << std::endl;
//        std::cout << "s0 " << currentPresetComposedNameComps[8].toStdString() << std::endl;
        
        if(!currentPresetComposedNameComps[3].toStdString().empty()
            && currentPresetComposedNameComps[3].toStdString() != ""
            && currentPresetComposedNameComps[3].toStdString() != " "
            && currentPresetComposedNameComps[3].toStdString() != DEFAULT_PRESET_INIT_NAME) {
            
            result = currentPresetComposedNameComps[3].toStdString().
                       append(" - ").append(result);
        }
        
        return result;
    }
    
    juce::String buildPatchNameFromString(std::string string) {
        //std::cout << "s0 " << string << std::endl;
        juce::StringArray stringComponents = explode(string, STRING_SEPARATOR);
        return buildPatchNameFromStringArray(stringComponents);
    }
    
    juce::String buildFolderNameFromStringArray(juce::StringArray currentPresetComposedNameComps) {
        return currentPresetComposedNameComps[3].toStdString();
    }
    
    juce::String buildOnlyPatchNameFromStringArray(juce::StringArray currentPresetComposedNameComps) {
        return currentPresetComposedNameComps[6].toStdString();
    }
    
    juce::String buildPatchName(juce::String presetComposedName) {
        return this->buildPatchNameFromString(presetComposedName.toStdString());
    }
    
    juce::String buildOnlyPatchName(juce::String presetComposedName) {
        juce::StringArray currentPresetComposedNameComps = this->explode(presetComposedName, STRING_SEPARATOR);
        
        return this->buildOnlyPatchNameFromStringArray(currentPresetComposedNameComps);
    }
    
    juce::String buildFolderName(juce::String presetComposedName) {
        juce::StringArray currentPresetComposedNameComps = this->explode(presetComposedName, STRING_SEPARATOR);
        
        return this->buildFolderNameFromStringArray(currentPresetComposedNameComps);
    }
    
    std::string implode(const std::vector<std::string> &elements,
                               const std::string &stringSeparator)
    {
        if (!elements.empty())
        {
            std::stringstream ss;
            auto it = elements.cbegin();
            while (true)
            {
                ss << *it++;
                if (it != elements.cend())
                    ss << stringSeparator;
                else
                    return ss.str();
            }
        }
        return "";
    }
    
    std::string buildPresetComposedName(std::string directoryIndex, std::string presetFolder, std::string presetName) {
        return directoryIndex
                                    .append(STRING_SEPARATOR)
                                    .append(presetFolder)
                                    .append(STRING_SEPARATOR)
                                    .append(presetName);
    }
    
    bool createNewPresetFolder(std::string newDirectoryName) {
        juce::File userPresetsFolder (juce::File (juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory))
                                      .getChildFile (PRESETS_PATH)
                                      .getChildFile(newDirectoryName));
        
        juce::Result r = userPresetsFolder.createDirectory();
        
        return !r.failed();
    }
    
    void writeNewPresetFile(std::string newPresetName,
                            std::string newDirectoryName,
                            std::string newPresetCreatorName,
                            std::string newPresetJson) {
        
        juce::File userPresetFile (juce::File (juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory))
                                        .getChildFile (PRESETS_PATH)
                                        .getChildFile(newDirectoryName)
                                        .getChildFile(newPresetName.append(".").append(PRESET_FILE_EXTENSION)));
        
        std::unique_ptr<juce::FileOutputStream> userPresetFileOutputStream = userPresetFile.createOutputStream();
        
        juce::var r = juce::JSON::parse(newPresetJson);
        
        
        std::cout << newPresetJson << std::endl;
        
        juce::JSON::writeToStream(*userPresetFileOutputStream, juce::JSON::parse(newPresetJson));
        
    }
    
    bool replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }
    
};




//https://stackoverflow.com/questions/13462001/ease-in-and-ease-out-animation-formula
/*juce::String js = “something to try”;
 std::string ss = (const char*) js;

 and the opposite

 std::string ss = “another try”;
 juce::String js = (const char*) ss.c_str();*/
