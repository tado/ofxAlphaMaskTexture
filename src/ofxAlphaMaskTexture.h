#pragma once
#define STRINGIFY(A) #A

#include "ofMain.h"

class ofxAlphaMaskTexture {
public:
    ofxAlphaMaskTexture(ofTexture topLayer, ofTexture bottomLayer, ofTexture maskLayer);
    void update();
    void draw();
    
    string frag;
    string vert;
    ofShader maskShader;
    
    ofTexture maskLayer;
    ofTexture topLayer;
    ofTexture bottomLayer;
    
    ofFbo maskFbo;
    ofFbo fbo;
    
    int width;
    int height;
    float maskScale;
};