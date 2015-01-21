#pragma once
#include "ofMain.h"

class ofxAlphaMaskTexture {
public:
    ofxAlphaMaskTexture(ofTexture topLayer, ofTexture bottomLayer, ofTexture maskLayer);
    void updateTopTexture(ofTexture topTexture);
    void update();
    void draw();
    
    ofShader maskShader;
    
    ofTexture maskLayer;
    ofTexture topLayer;
    ofTexture bottomLayer;
    
    int width;
    int height;
};