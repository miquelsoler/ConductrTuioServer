//
//  SettingsManager.h
//  ConductrEnter
//
//  Created by Miquel �ngel Soler on 25/5/15.
//
//

#pragma once

#ifndef __ConductrEnter__SettingsManager__
#define __ConductrEnter__SettingsManager__

#include <stdio.h>
#include "ofxJSON.h"

class SettingsManager
{
public:
    static SettingsManager &getInstance()
    {
        static SettingsManager instance;
        return instance;
    }

    // TUIO
    unsigned int    tuioClientPort;

    // OSC
    string          oscClientHost;
    unsigned int    oscClientPort;

private:

    SettingsManager();
    bool loadSettings();

    ofxJSONElement  json;
};

#endif /* defined(__ConductrEnter__SettingsManager__) */
