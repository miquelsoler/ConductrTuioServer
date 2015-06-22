#pragma once

#include "ofMain.h"
#include "TUIOHandler.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    // TUIO touch events
    virtual void tuioPressed(ofTouchEventArgs &touch);
    virtual void tuioReleased(ofTouchEventArgs &touch);
    virtual void tuioDragged(ofTouchEventArgs &touch);
};

