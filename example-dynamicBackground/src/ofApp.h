#pragma once

#include "ofMain.h"
#include "ofxAlphaMaskTexture.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxAlphaMaskTexture *alphaMask;
    ofImage maskImg;
    ofFbo bgFbo;

    
    ofVideoGrabber cam;
    static const int NUM = 100;
    ofVec2f velocity[NUM];
    ofVec2f location[NUM];
    float radius[NUM];
    ofColor color[NUM];
};