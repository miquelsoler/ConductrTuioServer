#pragma once

#include "ofMain.h"
#include "TUIOHandler.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    // TUIO touch events
    virtual void tuioTouchedDown(ofTouchEventArgs &touch);
    virtual void tuioTouchedUp(ofTouchEventArgs &touch);
    virtual void tuioDragged(ofTouchEventArgs &touch);

    ofxOscSender oscSender;

    ofTouchEventArgs lastTouchDown;
    ofTouchEventArgs lastTouchUp;
    ofTouchEventArgs lastTouchDrag;
};

