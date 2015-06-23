#include "ofApp.h"
#include "SettingsManager.h"

#pragma mark - Usual OF calls

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(ofColor::black);

    TUIOHandler::getInstance().init();

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &ofApp::tuioTouchedDown);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &ofApp::tuioTouchedUp);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &ofApp::tuioDragged);

    lastTouchDown.set(-1, -1);
    lastTouchUp.set(-1, -1);
    lastTouchDrag.set(-1, -1);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(ofColor::white);

    // Draw header
    string header1 = "Receiving TUIO messages from port " + ofToString(SettingsManager::getInstance().tuioClientPort);
    ofDrawBitmapString(header1, 10, 20);
//    string header2 = "Sending TUIO messages to " + SettingsManager::getInstance().tuioServerHost + ":" + ofToString(SettingsManager::getInstance().tuioServerPort);
//    ofDrawBitmapString(header2, 10, 40);

    // Draw last touch down
    string touchDown = "Touched down: ";
    if ((lastTouchDown.x == -1) && (lastTouchDown.y == -1))
        touchDown += "<NONE>";
    else
        touchDown += "(" + ofToString(lastTouchDown.x) + ", " + ofToString(lastTouchDown.y) + ")";
    ofDrawBitmapString(touchDown, 10, 80);

    // Draw last drag
    string touchDrag = "Dragged:      ";
    if ((lastTouchDrag.x == -1) && (lastTouchDrag.y == -1))
        touchDrag += "<NONE>";
    else
        touchDrag += "(" + ofToString(lastTouchDrag.x) + ", " + ofToString(lastTouchDrag.y) + ")";
    ofDrawBitmapString(touchDrag, 10, 100);

    // Draw last touch up
    string touchUp = "Touched up:   ";
    if ((lastTouchUp.x == -1) && (lastTouchUp.y == -1))
        touchUp += "<NONE>";
    else
        touchUp += "(" + ofToString(lastTouchUp.x) + ", " + ofToString(lastTouchUp.y) + ")";
    ofDrawBitmapString(touchUp, 10, 120);

//    TUIOHandler::getInstance().tuioClient->drawCursors(0, 255, 0);
}


#pragma mark - TUIO touch events

//--------------------------------------------------------------
void ofApp::tuioTouchedDown(ofTouchEventArgs &touch)
{
    lastTouchDown = touch;
    lastTouchUp.set(-1, -1);
    lastTouchDrag.set(-1, -1);
}

//--------------------------------------------------------------
void ofApp::tuioTouchedUp(ofTouchEventArgs &touch)
{
    lastTouchUp = touch;
}

//--------------------------------------------------------------
void ofApp::tuioDragged(ofTouchEventArgs &touch)
{
    lastTouchDrag = touch;
}
