#include "ofApp.h"
#include "SettingsManager.h"

#pragma mark - Usual OF calls

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(ofColor::black);

    TUIOHandler::getInstance().init();

    oscSender.setup(SettingsManager::getInstance().oscClientHost, SettingsManager::getInstance().oscClientPort);

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
    // Draw header
    string header = "Sending OSC messages to " + SettingsManager::getInstance().oscClientHost + ":" + ofToString(SettingsManager::getInstance().oscClientPort);
    ofDrawBitmapString(header, 10, 20);

    // Draw last touch down
    string touchDown = "Touched down: ";
    if ((lastTouchDown.x == -1) && (lastTouchDown.y == -1))
        touchDown += "<NONE>";
    else
        touchDown += "(" + ofToString(lastTouchDown.x) + ", " + ofToString(lastTouchDown.y) + ")";
    ofDrawBitmapString(touchDown, 10, 60);

    // Draw last drag
    string touchDrag = "Dragged:      ";
    if ((lastTouchDrag.x == -1) && (lastTouchDrag.y == -1))
        touchDrag += "<NONE>";
    else
        touchDrag += "(" + ofToString(lastTouchDrag.x) + ", " + ofToString(lastTouchDrag.y) + ")";
    ofDrawBitmapString(touchDrag, 10, 80);

    // Draw last touch up
    string touchUp = "Touched up:   ";
    if ((lastTouchUp.x == -1) && (lastTouchUp.y == -1))
        touchUp += "<NONE>";
    else
        touchUp += "(" + ofToString(lastTouchUp.x) + ", " + ofToString(lastTouchUp.y) + ")";
    ofDrawBitmapString(touchUp, 10, 100);
}


#pragma mark - TUIO touch events

//--------------------------------------------------------------
void ofApp::tuioTouchedDown(ofTouchEventArgs &touch)
{
    ofxOscMessage m;
    m.setAddress("/server/tuio/touchdown");
    m.addFloatArg(touch.x);
    m.addFloatArg(touch.y);
    oscSender.sendMessage(m);

    lastTouchDown = touch;
    lastTouchUp.set(-1, -1);
    lastTouchDrag.set(-1, -1);
}

//--------------------------------------------------------------
void ofApp::tuioTouchedUp(ofTouchEventArgs &touch)
{
    ofxOscMessage m;
    m.setAddress("/server/tuio/touchup");
    m.addFloatArg(touch.x);
    m.addFloatArg(touch.y);
    oscSender.sendMessage(m);

    lastTouchUp = touch;
}

//--------------------------------------------------------------
void ofApp::tuioDragged(ofTouchEventArgs &touch)
{
    ofxOscMessage m;
    m.setAddress("/server/tuio/drag");
    m.addFloatArg(touch.x);
    m.addFloatArg(touch.y);
    oscSender.sendMessage(m);

    lastTouchDrag = touch;
}
