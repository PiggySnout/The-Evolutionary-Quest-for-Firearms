#pragma once
#include "raylib.h"
#include <string>

inline const std::string GetSoundPath(std::string a) {
    static const std::string path =  GetApplicationDirectory() + "assets/sound/";
    return path + a;
}

inline const std::string GetDataPath(std::string a) {
    static const std::string path = GetApplicationDirectory() + "assets/Data/";
    return path + a;
}

inline const std::string GetAssetsPath(std::string a) {
    static const std::string path = GetApplicationDirectory() + "assets/textures/";
    return path + a;
}