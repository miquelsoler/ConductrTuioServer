//
//  TUIOHandler.cpp
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 13/6/15.
//
//

#include "TUIOHandler.h"

#include "SettingsManager.h"

///--------------------------------------------------------------
TUIOHandler::TUIOHandler()
{
    unsigned int clientPort = SettingsManager::getInstance().tuioClientPort;
    tuioClient = new ofxTuioClient();
    tuioClient->connect(clientPort);

    string oscServerHost = SettingsManager::getInstance().oscServerHost;
    unsigned int oscServerPort = SettingsManager::getInstance().oscServerPort;

    oscSender.setup(oscServerHost, oscServerPort);

//    string serverHost = SettingsManager::getInstance().tuioServerHost;
//    unsigned int serverPort = SettingsManager::getInstance().tuioServerPort;
//
//    tuioServer = new ofxTuioServer();
//    tuioServer->start((char *)serverHost.c_str(), serverPort);
}

///--------------------------------------------------------------
void TUIOHandler::init()
{
    ofAddListener(ofEvents().touchDown, this, &TUIOHandler::tuioTouchDown);
    ofAddListener(ofEvents().touchUp, this, &TUIOHandler::tuioTouchUp);
    ofAddListener(ofEvents().touchMoved, this, &TUIOHandler::tuioTouchMoved);
}

void TUIOHandler::buildMessageFromCursor(ofxOscMessage &m, TuioCursor *cursor)
{
    m.addIntArg(cursor->getTuioSourceID());
    m.addIntArg(cursor->getSessionID());
    m.addIntArg(cursor->getCursorID());
    m.addFloatArg(cursor->getX());
    m.addFloatArg(cursor->getY());
    m.addFloatArg(cursor->getXSpeed());
    m.addFloatArg(cursor->getYSpeed());
    m.addFloatArg(cursor->getMotionAccel());
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchDown(ofTouchEventArgs &touch)
{
    TuioCursor *cursor = getCursorForId(touch.id);

    ofxOscMessage m;
    m.setAddress("/tuio/touchdown");
    buildMessageFromCursor(m, cursor);
    oscSender.sendMessage(m);
    ofNotifyEvent(eventTouchDown, touch, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchUp(ofTouchEventArgs &touch)
{
    TuioCursor *cursor = getCursorForId(touch.id);

    ofxOscMessage m;
    m.setAddress("/tuio/touchup");
    buildMessageFromCursor(m, cursor);
    oscSender.sendMessage(m);
    ofNotifyEvent(eventTouchUp, touch, this);
}

///--------------------------------------------------------------
void TUIOHandler::tuioTouchMoved(ofTouchEventArgs &touch)
{
    TuioCursor *cursor = getCursorForId(touch.id);

    ofxOscMessage m;
    m.setAddress("/tuio/drag");
    buildMessageFromCursor(m, cursor);
    oscSender.sendMessage(m);
    ofNotifyEvent(eventTouchDrag, touch, this);
}

///--------------------------------------------------------------
float TUIOHandler::getDistBetweenCursors(int cursorId1, int cursorId2)
{
    TuioCursor *c1 = tuioClient->client->getTuioCursor(cursorId1);
    TuioCursor *c2 = tuioClient->client->getTuioCursor(cursorId2);

    if ((c1 == NULL) || (c2 == NULL)) return 0;

    ofVec2f screenC1 = TUIOHandler::tuioToScreenCoords(c1->getPosition().getX(), c1->getPosition().getY());
    ofVec2f screenC2 = TUIOHandler::tuioToScreenCoords(c2->getPosition().getX(), c2->getPosition().getY());

    return ofDist(screenC1.x, screenC1.y, screenC2.x, screenC2.y);
}

///--------------------------------------------------------------
ofVec2f TUIOHandler::tuioToScreenCoords(float tuioX, float tuioY)
{
    ofVec2f screenCoords(ofMap(tuioX, 0, 1, 0, ofGetWidth()),
                         ofMap(tuioY, 0, 1, 0, ofGetHeight()));
    return screenCoords;
}

///--------------------------------------------------------------
TuioCursor *TUIOHandler::getCursorForId(int cursorId)
{
    TuioCursor *cursor = tuioClient->client->getTuioCursor(cursorId);
    return cursor;
}
