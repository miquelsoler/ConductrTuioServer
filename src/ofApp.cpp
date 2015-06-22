#include "ofApp.h"

#pragma mark - Usual OF calls

//--------------------------------------------------------------
void ofApp::setup()
{
    TUIOHandler::getInstance().init();

    ofAddListener(TUIOHandler::getInstance().eventTouchDown, this, &ofApp::tuioPressed);
    ofAddListener(TUIOHandler::getInstance().eventTouchUp, this, &ofApp::tuioReleased);
    ofAddListener(TUIOHandler::getInstance().eventTouchDrag, this, &ofApp::tuioDragged);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

#pragma mark - TUIO touch events

//--------------------------------------------------------------
void ofApp::tuioPressed(ofTouchEventArgs &touch)
{
    cout << "Pressed" << endl;
}

//--------------------------------------------------------------
void ofApp::tuioReleased(ofTouchEventArgs &touch)
{
    cout << "Released" << endl;
}

//--------------------------------------------------------------
void ofApp::tuioDragged(ofTouchEventArgs &touch)
{
    cout << "Dragged" << endl;
}
