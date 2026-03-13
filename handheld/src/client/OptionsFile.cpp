#include "OptionsFile.h"
#include <stdio.h>
#include <string.h>
#include "../platform/log.h"

#include <string>

#ifdef _WIN32
    // For Windows mkdir
    #include <direct.h>
#elif defined(STANDALONE_SERVER) || defined(__linux__) || defined(__APPLE__)
    // For Linux / macOS / server builds
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

OptionsFile::OptionsFile() {
#ifdef __APPLE__
    settingsPath = "./Documents/options.txt";
#elif defined(ANDROID)
    settingsPath = "/sdcard/games/com.mojang/minecraftpe/options.txt";
#elif defined(__VITA__)
    settingsPath = "ux0:data/minecraftpe/games/com.mojang/minecraftpe/options.txt";
#else
    settingsPath = "options.txt";
#endif
}

void OptionsFile::createDirectories(std::string& path) {
    for (int i = 0; i < path.length(); i++) {
        if (path[i] == '/' || path[i] == '\\') {
#ifdef _WIN32
            mkdir(path.substr(0, i).c_str());
#elif defined(STANDALONE_SERVER) || defined(__linux__) || defined(__APPLE__)
            mkdir(path.substr(0, i).c_str(), 0777); // full permissions for directories
#endif
        }
    }
}

void OptionsFile::save(const StringVector& settings) {
    createDirectories(settingsPath);
    FILE* pFile = fopen(settingsPath.c_str(), "w");

    if (pFile != NULL) {
        for (StringVector::const_iterator it = settings.begin(); it != settings.end(); ++it) {
            fprintf(pFile, "%s\n", it->c_str());
        }
        fclose(pFile);
    }
}

StringVector OptionsFile::getOptionStrings() {
    StringVector returnVector;
    FILE* pFile = fopen(settingsPath.c_str(), "r");
    if (pFile != NULL) {
        char lineBuff[128];
        while (fgets(lineBuff, sizeof lineBuff, pFile)) {
            if (strlen(lineBuff) > 2) {
                std::string line = lineBuff;

                if (!line.empty() && line[line.length() - 1] == '\n') {
                    line.erase(line.length() - 1);
                }
                size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    returnVector.push_back(line.substr(0, colonPos));
                    returnVector.push_back(line.substr(colonPos + 1));
                }
            }
        }
        fclose(pFile);
    }
    return returnVector;
}