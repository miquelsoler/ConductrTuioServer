//
//  SettingsManager.cpp
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 25/5/15.
//
//

#include "SettingsManager.h"

const std::string FILENAME = "settings.json";

///--------------------------------------------------------------
SettingsManager::SettingsManager()
{
    bool parserResult = loadSettings();
    if (!parserResult)
    {
        ofLog(OF_LOG_ERROR, "BAD FORMAT IN settings.json. Now quitting...");
        std::exit(EXIT_FAILURE);
    }
}

///--------------------------------------------------------------
bool SettingsManager::loadSettings()
{
    // JSON parse

    bool parsingSuccessful = json.open(FILENAME);
    cout << "PARSING RESULT: " << parsingSuccessful << endl;

    // TUIO
    tuioClientPort = json["TUIO"]["Client Port"].asUInt();

    // OSC
    oscClientHost = json["OSC"]["Client Host"].asString();
    oscClientPort = json["OSC"]["Client Port"].asUInt();

    return parsingSuccessful;
}
