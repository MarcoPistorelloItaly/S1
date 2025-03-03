/*
  ==============================================================================

    Constants.h
    Created: 31 Dec 2024 11:26:59am
    Author:  Marco

  ==============================================================================
*/

#pragma once

#define OSCILLATOR_MODE_SINE = 1;
#define OSCILLATOR_MODE_SAW = 2;
#define OSCILLATOR_MODE_SQUARE = 3;
#define OSCILLATOR_MODE_TRIANGLE = 4;

#define STRING_SEPARATOR "|||"
#define PROGRAM_SELECTOR_HEIGHT 40

#define COMMON_APPLICATION_DATA_DIRECTORY_INDEX "1"
#define USER_APPLICATION_DATA_DIRECTORY_INDEX "2"

#define PRESET_FILE_EXTENSION "s1"

#define ADSR_1_ATTACK_ID "ADSR_1_ATTACK_ID"
#define ADSR_1_ATTACK_NAME "OSC1 Attack"

#define ADSR_1_DECAY_ID "ADSR_1_DECAY_ID"
#define ADSR_1_DECAY_NAME "OSC1 Decay"

#define ADSR_1_SUSTAIN_ID "ADSR_1_SUSTAIN_ID"
#define ADSR_1_SUSTAIN_NAME "OSC1 Sustain"

#define ADSR_1_RELEASE_ID "ADSR_1_RELEASE_ID"
#define ADSR_1_RELEASE_NAME "OSC1 Release"

#define ADSR_2_ATTACK_ID "ADSR_2_ATTACK_ID"
#define ADSR_2_ATTACK_NAME "OSC2 Attack"

#define ADSR_2_DECAY_ID "ADSR_2_DECAY_ID"
#define ADSR_2_DECAY_NAME "OSC2 Decay"

#define ADSR_2_SUSTAIN_ID "ADSR_2_SUSTAIN_ID"
#define ADSR_2_SUSTAIN_NAME "OSC2 Sustain"

#define ADSR_2_RELEASE_ID "ADSR_2_RELEASE_ID"
#define ADSR_2_RELEASE_NAME "OSC2 Release"

#define ADSR_ATTACK_MIN "0.01f"
#define ADSR_ATTACK_MAX "5.0f"
#define ADSR_ATTACK_DEFAULT "0.1f"

#define ADSR_DECAY_MIN "0.1f"
#define ADSR_DECAY_MAX "2.0f"
#define ADSR_DECAY_DEFAULT "1.0f"

#define ADSR_SUSTAIN_MIN "0.0f"
#define ADSR_SUSTAIN_MAX "1.0f"
#define ADSR_SUSTAIN_DEFAULT "0.8f"

#define ADSR_RELEASE_MIN "0.1f"
#define ADSR_RELEASE_MAX "5.0f"
#define ADSR_RELEASE_DEFAULT "0.8f"

#define WAVE_TYPE_1_ID "WAVE_TYPE_1_ID"
#define WAVE_TYPE_1_NAME "OSC 1 Wave Type"

#define WAVE_TYPE_2_ID "WAVE_TYPE_2_ID"
#define WAVE_TYPE_2_NAME "OSC 2 Wave Type"

#define WAVE_TYPE_MIN "0.0f"
#define WAVE_TYPE_MAX "3.0f"
#define WAVE_TYPE_DEFAULT "0.0f"

#define OSC_WIDTH 100
#define OSC_HEIGHT 100
#define OSC_PADDING 25

#define OSC_QTY 4

#define DISTORTION_1_DRIVE_ID "DISTORTION_1_DRIVE_ID"
#define DISTORTION_1_DRIVE_NAME "OSC 1 Distortion Drive"

#define DISTORTION_1_RANGE_ID "DISTORTION_1_RANGE_ID"
#define DISTORTION_1_RANGE_NAME "OSC 1 Distortion Range"

#define DISTORTION_1_BLEND_ID "DISTORTION_1_BLEND_ID"
#define DISTORTION_1_BLEND_NAME "OSC 1 Distortion Blend"

#define DISTORTION_1_VOLUME_ID "DISTORTION_1_VOLUME_ID"
#define DISTORTION_1_VOLUME_NAME "OSC 1 Distortion Volume"

#define DISTORTION_2_DRIVE_ID "DISTORTION_2_DRIVE_ID"
#define DISTORTION_2_DRIVE_NAME "OSC 2 Distortion Drive"

#define DISTORTION_2_RANGE_ID "DISTORTION_2_RANGE_ID"
#define DISTORTION_2_RANGE_NAME "OSC 2 Distortion Range"

#define DISTORTION_2_BLEND_ID "DISTORTION_2_BLEND_ID"
#define DISTORTION_2_BLEND_NAME "OSC 2 Distortion Blend"

#define DISTORTION_2_VOLUME_ID "DISTORTION_2_VOLUME_ID"
#define DISTORTION_2_VOLUME_NAME "OSC 2 Distortion Volume"

#define DISTORTION_1_SWITCH_ID "DISTORTION_1_SWITCH_ID"
#define DISTORTION_1_SWITCH_NAME "OSC 1 Distortion Switch"

#define DISTORTION_2_SWITCH_ID "DISTORTION_2_SWITCH_ID"
#define DISTORTION_2_SWITCH_NAME "OSC 2 Distortion Switch"

#define DISTORTION_DRIVE_MIN "1.0f"
#define DISTORTION_DRIVE_MAX "5.0f"
#define DISTORTION_DRIVE_DEFAULT "0.0f"

#define DISTORTION_RANGE_MIN "0.0f"
#define DISTORTION_RANGE_MAX "3000.0f"
#define DISTORTION_RANGE_DEFAULT "0.0f"

#define DISTORTION_BLEND_MIN "0.0f"
#define DISTORTION_BLEND_MAX "1.0f"
#define DISTORTION_BLEND_DEFAULT "0.0f"

#define DISTORTION_VOLUME_MIN "0.0f"
#define DISTORTION_VOLUME_MAX "3.0f"
#define DISTORTION_VOLUME_DEFAULT "0.5f"

#define LEVEL_1_ID "level1ID"
#define LEVEL_1_NAME "level1Name"

#define LEVEL_2_ID "level2ID"
#define LEVEL_2_NAME "level2Name"

#define LEVEL_MIN "0.0f"
#define LEVEL_MAX "1.0f"
#define LEVEL_DEFAULT "0.5f"

#define FILTER_1_TYPE_ID "FILTER_1_TYPE_ID"
#define FILTER_1_TYPE_NAME "Filter 1 Type"

#define FILTER_1_RES_ID "FILTER_1_RES_ID"
#define FILTER_1_RES_NAME "Filter 1 Res"

#define FILTER_1_CUTOFF_ID "FILTER_1_CUTOFF_ID"
#define FILTER_1_CUTOFF_NAME "Filter 1 Cutoff Frequency"

#define FILTER_2_TYPE_ID "FILTER_2_TYPE_ID"
#define FILTER_2_TYPE_NAME "Filter 2 Type"

#define FILTER_2_RES_ID "FILTER_2_RES_ID"
#define FILTER_2_RES_NAME "Filter 2 Res"

#define FILTER_2_CUTOFF_ID "FILTER_2_CUTOFF_ID"
#define FILTER_2_CUTOFF_NAME "Filter 2 Cutoff Frequency"

#define FILTER_1_ATTACK_ID "FILTER_1_ATTACK_ID"
#define FILTER_1_ATTACK_NAME "Filter 1 Attack"

#define FILTER_2_ATTACK_ID "FILTER_2_ATTACK_ID"
#define FILTER_2_ATTACK_NAME "Filter 2 Attack"

#define FILTER_1_SWITCH_ID "FILTER_1_SWITCH_ID"
#define FILTER_1_SWITCH_NAME "Filter 1 Switch"

#define FILTER_2_SWITCH_ID "FILTER_2_SWITCH_ID"
#define FILTER_2_SWITCH_NAME "Filter 2 Switch"

#define FILTER_TYPE_MIN "0.0f"
#define FILTER_TYPE_MAX "2.0f"
#define FILTER_TYPE_DEFAULT "0.0f"

#define FILTER_RES_MIN "1.0f"
#define FILTER_RES_MAX "24.0f"
#define FILTER_RES_DEFAULT "2.0f"

#define FILTER_RES_DIAL_LABEL "Filter Resonance"

#define FILTER_CUTOFF_MIN "20.0f"
#define FILTER_CUTOFF_MAX "20000.0f"
#define FILTER_CUTOFF_DEFAULT "2000.0f"

#define FILTER_ATTACK_MIN "0.0f"
#define FILTER_ATTACK_MAX "5.0f"
#define FILTER_ATTACK_DEFAULT "0.0f"

#define FILTER_WIDTH 100
#define FILTER_HEIGHT 100
#define FILTER_PADDING 25

#define FILTER_MENU_MIN 0.0f
#define FILTER_MENU_MAX 2.0f
#define FILTER_MENU_DEFAULT 0.0f

#define FILTER_QTY 3

#define CURRENT_PRESET_COMPOSED_NAME "currentPresetComposedName"
#define DEFAULT_PRESET_INIT_NAME "Init"
#define DEFAULT_CURRENT_PRESET_CREATOR_NAME "MarcoPysto"

#define GLOBAL_WIDTH 1100
#define SYNTH_ENGINE_WIDTH 1100
#define SYNTH_ENGINE_HEIGHT 150

#define WHAT_TO_SHOW_FOLDERS 0
#define WHAT_TO_SHOW_PRESETS 1

#define INPUT_TEXT_WIDTH 200
#define INPUT_TEXT_HEIGHT 30

#define STANDARD_PADDING 10

#define S1_PRESETS_FOLDER "S1"
#define FACTORY_PRESETS "Factory Presets"
#define USER_PRESETS "User Presets"

#define PRESETS_PATH "Audio/Presets/S1/Factory Presets"

#define NAME_MAX_LENGTH 20
#define NAME_ALLOWED_CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_1234567890 "

#define PRESET_JSON_TEMPLATE "{\"license\": \"Patch (c) by CREATOR_PLACEHOLDER.  This patch is licensed under a Creative Commons Attribution 4.0 International License.  You should have received a copy of the license along with this work.  If not, see <http://creativecommons.org/licenses/by/4.0/>.\",\"preset_name\": \"PRESET_NAME_PLACEHOLDER\",\"folder_name\": \"FOLDER_PLACEHOLDER\",\"author\": \"CREATOR_PLACEHOLDER\",\"settings\": SETTINGS_PLACEHOLDER}"

#define VERSION "0.0.2"

#define NOISE_GENERATOR_SWITCH_ID "noiseGeneratorSwitchParameter"
#define NOISE_GENERATOR_SWITCH_NAME "noiseGeneratorSwitchParameter"

#define FONT_SIZE_1 13.0f

#define VOLUME_LABEL_1 "volumeLabel1"
#define VOLUME_LABEL_2 "volumeLabel2"

#define PARAM_VERSION_HINT 1

/*
 
 {
   "license": "Patch (c) by MarcoPistorello.  This patch is licensed under a Creative Commons Attribution 4.0 International License.  You should have received a copy of the license along with this work.  If not, see <http://creativecommons.org/licenses/by/4.0/>.",
   "synth_version": "0.0.1",
   "patch_name": "test4",
   "folder_name": "FolderTest1",
   "author": "MarcoPistorello",
   "settings": {
     "attack1ID": 3
   }
 }
 
 
std::string a[1];
a[0] = std::string("A");
std::map<std::string, std::string*[1]> asd;
asd.insert(std::pair<std::string,std::string*[1]>(std::string("A"), {std::string("A")}));*/

class Constants
{
    public:
    
        Constants()
        {
            std::map<std::string,std::string> LEVEL1 = { {"ID", LEVEL_1_ID},
                                                            {"NAME", LEVEL_1_NAME},
                                                            {"MIN", LEVEL_MIN},
                                                            {"MAX", LEVEL_MAX},
                                                            {"DEFAULT", LEVEL_DEFAULT}
            };
            
            std::map<std::string,std::string> LEVEL2 = { {"ID", LEVEL_2_ID},
                                                            {"NAME", LEVEL_2_NAME},
                                                            {"MIN", LEVEL_MIN},
                                                            {"MAX", LEVEL_MAX},
                                                            {"DEFAULT", LEVEL_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC1_ATTACK = { {"ID", ADSR_1_ATTACK_ID},
                                                            {"NAME", ADSR_1_ATTACK_NAME},
                                                            {"MIN", ADSR_ATTACK_MIN},
                                                            {"MAX", ADSR_ATTACK_MAX},
                                                            {"DEFAULT", ADSR_ATTACK_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC1_DECAY = { {"ID", ADSR_1_DECAY_ID},
                                                            {"NAME", ADSR_1_DECAY_NAME},
                                                            {"MIN", ADSR_DECAY_MIN},
                                                            {"MAX", ADSR_DECAY_MAX},
                                                            {"DEFAULT", ADSR_DECAY_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC1_SUSTAIN = { {"ID", ADSR_1_SUSTAIN_ID},
                                                            {"NAME", ADSR_1_SUSTAIN_NAME},
                                                            {"MIN", ADSR_SUSTAIN_MIN},
                                                            {"MAX", ADSR_SUSTAIN_MAX},
                                                            {"DEFAULT", ADSR_SUSTAIN_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC1_RELEASE = { {"ID", ADSR_1_RELEASE_ID},
                                                            {"NAME", ADSR_1_RELEASE_NAME},
                                                            {"MIN", ADSR_RELEASE_MIN},
                                                            {"MAX", ADSR_RELEASE_MAX},
                                                            {"DEFAULT", ADSR_RELEASE_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC2_ATTACK = { {"ID", ADSR_2_ATTACK_ID},
                                                            {"NAME", ADSR_2_ATTACK_NAME},
                                                            {"MIN", ADSR_ATTACK_MIN},
                                                            {"MAX", ADSR_ATTACK_MAX},
                                                            {"DEFAULT", ADSR_ATTACK_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC2_DECAY = { {"ID", ADSR_2_DECAY_ID},
                                                            {"NAME", ADSR_2_DECAY_NAME},
                                                            {"MIN", ADSR_DECAY_MIN},
                                                            {"MAX", ADSR_DECAY_MAX},
                                                            {"DEFAULT", ADSR_DECAY_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC2_SUSTAIN = { {"ID", ADSR_2_SUSTAIN_ID},
                                                            {"NAME", ADSR_2_SUSTAIN_NAME},
                                                            {"MIN", ADSR_SUSTAIN_MIN},
                                                            {"MAX", ADSR_SUSTAIN_MAX},
                                                            {"DEFAULT", ADSR_SUSTAIN_DEFAULT}
            };
            
            std::map<std::string,std::string> OSC2_RELEASE = { {"ID", ADSR_2_RELEASE_ID},
                                                            {"NAME", ADSR_2_RELEASE_NAME},
                                                            {"MIN", ADSR_RELEASE_MIN},
                                                            {"MAX", ADSR_RELEASE_MAX},
                                                            {"DEFAULT", ADSR_RELEASE_DEFAULT}
            };
            
            std::map<std::string,std::string> WAVE_TYPE_1 = { {"ID", WAVE_TYPE_1_ID},
                                                            {"NAME", WAVE_TYPE_1_NAME},
                                                            {"MIN", WAVE_TYPE_MIN},
                                                            {"MAX", WAVE_TYPE_MAX},
                                                            {"DEFAULT", WAVE_TYPE_DEFAULT}
            };
            
            std::map<std::string,std::string> WAVE_TYPE_2 = { {"ID", WAVE_TYPE_2_ID},
                                                            {"NAME", WAVE_TYPE_2_NAME},
                                                            {"MIN", WAVE_TYPE_MIN},
                                                            {"MAX", WAVE_TYPE_MAX},
                                                            {"DEFAULT", WAVE_TYPE_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_DRIVE_1 = { {"ID", DISTORTION_1_DRIVE_ID},
                                                            {"NAME", DISTORTION_1_DRIVE_NAME},
                                                            {"MIN", DISTORTION_DRIVE_MIN},
                                                            {"MAX", DISTORTION_DRIVE_MAX},
                                                            {"DEFAULT", DISTORTION_DRIVE_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_RANGE_1 = { {"ID", DISTORTION_1_RANGE_ID},
                                                            {"NAME", DISTORTION_1_RANGE_NAME},
                                                            {"MIN", DISTORTION_RANGE_MIN},
                                                            {"MAX", DISTORTION_RANGE_MAX},
                                                            {"DEFAULT", DISTORTION_RANGE_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_BLEND_1 = { {"ID", DISTORTION_1_BLEND_ID},
                                                            {"NAME", DISTORTION_1_BLEND_NAME},
                                                            {"MIN", DISTORTION_BLEND_MIN},
                                                            {"MAX", DISTORTION_BLEND_MAX},
                                                            {"DEFAULT", DISTORTION_BLEND_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_VOLUME_1 = { {"ID", DISTORTION_1_VOLUME_ID},
                                                            {"NAME", DISTORTION_1_VOLUME_NAME},
                                                            {"MIN", DISTORTION_VOLUME_MIN},
                                                            {"MAX", DISTORTION_VOLUME_MAX},
                                                            {"DEFAULT", DISTORTION_VOLUME_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_DRIVE_2 = { {"ID", DISTORTION_2_DRIVE_ID},
                                                            {"NAME", DISTORTION_2_DRIVE_NAME},
                                                            {"MIN", DISTORTION_DRIVE_MIN},
                                                            {"MAX", DISTORTION_DRIVE_MAX},
                                                            {"DEFAULT", DISTORTION_DRIVE_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_RANGE_2 = { {"ID", DISTORTION_2_RANGE_ID},
                                                            {"NAME", DISTORTION_2_RANGE_NAME},
                                                            {"MIN", DISTORTION_RANGE_MIN},
                                                            {"MAX", DISTORTION_RANGE_MAX},
                                                            {"DEFAULT", DISTORTION_RANGE_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_BLEND_2 = { {"ID", DISTORTION_2_BLEND_ID},
                                                            {"NAME", DISTORTION_2_BLEND_NAME},
                                                            {"MIN", DISTORTION_BLEND_MIN},
                                                            {"MAX", DISTORTION_BLEND_MAX},
                                                            {"DEFAULT", DISTORTION_BLEND_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_VOLUME_2 = { {"ID", DISTORTION_2_VOLUME_ID},
                                                            {"NAME", DISTORTION_2_VOLUME_NAME},
                                                            {"MIN", DISTORTION_VOLUME_MIN},
                                                            {"MAX", DISTORTION_VOLUME_MAX},
                                                            {"DEFAULT", DISTORTION_VOLUME_DEFAULT}
            };
            
            std::map<std::string,std::string> DISTORTION_SWITCH_1 = { {"ID", DISTORTION_1_SWITCH_ID},
                                                            {"NAME", DISTORTION_1_SWITCH_NAME},
                                                            {"MIN", "0"},
                                                            {"MAX", "1"},
                                                            {"DEFAULT", "0"}
            };
            
            std::map<std::string,std::string> DISTORTION_SWITCH_2 = { {"ID", DISTORTION_2_SWITCH_ID},
                                                            {"NAME", DISTORTION_2_SWITCH_NAME},
                                                            {"MIN", "0"},
                                                            {"MAX", "1"},
                                                            {"DEFAULT", "0"}
            };
            
            std::map<std::string,std::string> FILTER_1_TYPE = { {"ID", FILTER_1_TYPE_ID},
                                                            {"NAME", FILTER_1_TYPE_NAME},
                                                            {"MIN", FILTER_TYPE_MIN},
                                                            {"MAX", FILTER_TYPE_MAX},
                                                            {"DEFAULT", FILTER_TYPE_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_2_TYPE = { {"ID", FILTER_2_TYPE_ID},
                                                            {"NAME", FILTER_2_TYPE_NAME},
                                                            {"MIN", FILTER_TYPE_MIN},
                                                            {"MAX", FILTER_TYPE_MAX},
                                                            {"DEFAULT", FILTER_TYPE_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_1_RES = { {"ID", FILTER_1_RES_ID},
                                                            {"NAME", FILTER_1_RES_NAME},
                                                            {"MIN", FILTER_RES_MIN},
                                                            {"MAX", FILTER_RES_MAX},
                                                            {"DEFAULT", FILTER_RES_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_2_RES = { {"ID", FILTER_2_RES_ID},
                                                            {"NAME", FILTER_2_RES_NAME},
                                                            {"MIN", FILTER_RES_MIN},
                                                            {"MAX", FILTER_RES_MAX},
                                                            {"DEFAULT", FILTER_RES_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_1_CUTOFF = { {"ID", FILTER_1_CUTOFF_ID},
                                                            {"NAME", FILTER_1_CUTOFF_NAME},
                                                            {"MIN", FILTER_CUTOFF_MIN},
                                                            {"MAX", FILTER_CUTOFF_MAX},
                                                            {"DEFAULT", FILTER_CUTOFF_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_2_CUTOFF = { {"ID", FILTER_2_CUTOFF_ID},
                                                            {"NAME", FILTER_2_CUTOFF_NAME},
                                                            {"MIN", FILTER_CUTOFF_MIN},
                                                            {"MAX", FILTER_CUTOFF_MAX},
                                                            {"DEFAULT", FILTER_CUTOFF_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_1_ATTACK = { {"ID", FILTER_1_ATTACK_ID},
                                                            {"NAME", FILTER_1_ATTACK_NAME},
                                                            {"MIN", FILTER_ATTACK_MIN},
                                                            {"MAX", FILTER_ATTACK_MAX},
                                                            {"DEFAULT", FILTER_ATTACK_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_2_ATTACK = { {"ID", FILTER_2_ATTACK_ID},
                                                            {"NAME", FILTER_2_ATTACK_NAME},
                                                            {"MIN", FILTER_ATTACK_MIN},
                                                            {"MAX", FILTER_ATTACK_MAX},
                                                            {"DEFAULT", FILTER_ATTACK_DEFAULT}
            };
            
            std::map<std::string,std::string> FILTER_1_SWITCH = { {"ID", FILTER_1_SWITCH_ID},
                                                            {"NAME", FILTER_1_SWITCH_NAME},
                                                            {"MIN", "0"},
                                                            {"MAX", "1"},
                                                            {"DEFAULT", "0"}
            };
            
            std::map<std::string,std::string> FILTER_2_SWITCH = { {"ID", FILTER_2_SWITCH_ID},
                                                            {"NAME", FILTER_2_SWITCH_NAME},
                                                            {"MIN", "0"},
                                                            {"MAX", "1"},
                                                            {"DEFAULT", "0"}
            };
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(LEVEL_1_ID,LEVEL1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(LEVEL_2_ID,LEVEL2));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_1_ATTACK_ID,OSC1_ATTACK));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_1_DECAY_ID,OSC1_DECAY));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_1_SUSTAIN_ID,OSC1_SUSTAIN));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_1_RELEASE_ID,OSC1_RELEASE));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_2_ATTACK_ID,OSC2_ATTACK));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_2_DECAY_ID,OSC2_DECAY));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_2_SUSTAIN_ID,OSC2_SUSTAIN));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(ADSR_2_RELEASE_ID,OSC2_RELEASE));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(WAVE_TYPE_1_ID,WAVE_TYPE_1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(WAVE_TYPE_2_ID,WAVE_TYPE_2));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_1_DRIVE_ID,DISTORTION_DRIVE_1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_1_RANGE_ID,DISTORTION_RANGE_1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_1_BLEND_ID,DISTORTION_BLEND_1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_1_VOLUME_ID,DISTORTION_VOLUME_1));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_2_DRIVE_ID,DISTORTION_DRIVE_2));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_2_RANGE_ID,DISTORTION_RANGE_2));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_2_BLEND_ID,DISTORTION_BLEND_2));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_2_VOLUME_ID,DISTORTION_VOLUME_2));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_1_SWITCH_ID,DISTORTION_SWITCH_1));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(DISTORTION_2_SWITCH_ID,DISTORTION_SWITCH_2));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_1_TYPE_ID,FILTER_1_TYPE));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_2_TYPE_ID,FILTER_2_TYPE));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_1_RES_ID,FILTER_1_RES));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_2_RES_ID,FILTER_2_RES));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_1_CUTOFF_ID,FILTER_1_CUTOFF));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_2_CUTOFF_ID,FILTER_2_CUTOFF));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_1_ATTACK_ID,FILTER_1_ATTACK));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_2_ATTACK_ID,FILTER_2_ATTACK));
            
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_1_SWITCH_ID,FILTER_1_SWITCH));
            PARAMETERS_GLOBAL_MAP.insert(std::pair<std::string,std::map<std::string,std::string>>(FILTER_2_SWITCH_ID,FILTER_2_SWITCH));
        }
    
    float getParamValue(std::string paramId, std::string value) {
        std::map<std::string,std::string> PARAM_VALUES = PARAMETERS_GLOBAL_MAP.at(paramId);
        std::string paramValue = PARAM_VALUES[std::string(value)];
        float paramValueFloat = std::stof(paramValue);
        return paramValueFloat;
    }
    
    juce::String getParamValueString(std::string paramId, std::string value) {
        std::map<std::string,std::string> PARAM_VALUES = PARAMETERS_GLOBAL_MAP.at(paramId);
        std::string paramValue = PARAM_VALUES[std::string(value)];
        return (juce::String)paramValue;
    }
    
    std::map<std::string,std::map<std::string,std::string>> getParametersGlobalMap() {
        return PARAMETERS_GLOBAL_MAP;
    }
    
    juce::Colour getRotarySliderDisabledColour() {
        juce::Colour disabledColour = juce::Colours::darkslategrey;
        return disabledColour;
    }
    
    juce::Colour getRotarySliderFillDisabledColour() {
        juce::Colour disabledColour = juce::Colours::darkgrey;
        return disabledColour;
    }
    
    juce::Colour getRotarySliderEnabledColour() {
        juce::Colour enabledColour = juce::Colours::skyblue;
        return enabledColour;
    }
    
    juce::Colour getRotarySliderFillDarkColour() {
        juce::Colour rotarySliderFillDarkColour = juce::Colours::black;
        return rotarySliderFillDarkColour;
    }
    
    juce::Colour getRotarySliderFillRed() {
        juce::Colour rotarySliderFillDarkColour = juce::Colours::red;
        return rotarySliderFillDarkColour;
    }

    private :
        std::map<std::string,std::map<std::string,std::string>> PARAMETERS_GLOBAL_MAP;

    public:
    
};
