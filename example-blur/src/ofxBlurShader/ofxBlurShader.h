#pragma once 

#include "ofMain.h"

class ofxBlurShader {
public:
	
    ofxBlurShader(); 
    
	void setup(float w, float h);
	void begin(float amount=5, int iterations=2);
	void end();
	void draw(float x=0, float y=0, float w=0, float h=0);
    
    int iterations;
    float amount;
    bool enabled;
    
    ofFbo fbo1,fbo2;
    ofShader hShader, vShader;

private:
    bool initialized;
};

