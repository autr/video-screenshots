#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(ofKeyEventArgs& e);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofVideoPlayer player;
    void scrollPlayer(int x, int y);
    string currentName;
    int dotSize;
    float flashTime;
    float snapTime;
    ofImage img;
    ofRectangle box;
    ofFile lastOpened;
};
