/*
 *  ofxBlurShader.cpp
 *
 *  Created by Rick Companje on 25-10-10.
 *  updated on 15-07-11 for of007
 *  Based on the blurShader example by Theo
 *
 */

#include "ofxBlurShader.h"

ofxBlurShader::ofxBlurShader() {
    enabled = false;
    initialized = false;
}

void ofxBlurShader::setup(float w, float h) {
    
	fbo1.allocate(w,h);
	fbo2.allocate(w,h);
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();
    fbo2.begin();
    ofClear(0, 0, 0);
    fbo2.end();
	
    string vertexShader =
    "#version 120\n \
    varying vec2 texCoordVarying;\
    void main(void)\
    {\
        texCoordVarying = gl_MultiTexCoord0.xy;\
        gl_Position = ftransform();\
    }";
    
    //what the blur shader does: it takes blurAmnt as input and takes for each 'pixel' / fragment a
    //weighted average of itself and 8 horizontal neighbours (which neighbours depends on the blurAmnt
    
    string fragmentShaderHorizontal =
    "#version 120\n \
    uniform sampler2DRect tex0;\
    uniform float blurAmnt;\
    varying vec2 texCoordVarying;\
    void main()\
    {\
        vec4 color;\
        color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -4.0, 0.0));\
        color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -3.0, 0.0));\
        color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -2.0, 0.0));\
        color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -1.0, 0.0));\
        color += 5.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt, 0));\
        color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 1.0, 0.0));\
        color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 2.0, 0.0));\
        color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 3.0, 0.0));\
        color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 4.0, 0.0));\
        color /= 25.0;\
        gl_FragColor = color;\
    }";
    
    // same but now for vertical neighbours
    
    string fragmentShaderVertical =
    "#version 120\n \
    uniform sampler2DRect tex0;\
    uniform float blurAmnt;\
    varying vec2 texCoordVarying;\
    void main()\
    {\
        vec4 color;\
        color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 4.0));\
        color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 3.0));\
        color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 2.0));\
        color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 1.0));\
        color += 5.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt));\
        color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -1.0));\
        color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -2.0));\
        color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -3.0));\
        color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -4.0));\
        color /= 25.0;\
        gl_FragColor = color;\
    }";
	
    
    vShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderVertical);
    vShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
    vShader.linkProgram();
    
    hShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderHorizontal);
    hShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
    hShader.linkProgram();
    
    initialized = true;
    enabled = true;
}

void ofxBlurShader::begin(float amount, int iterations) {
    if (!initialized) ofLog(OF_LOG_ERROR, "ofxBlurShader::setup(w,h) needs to be called first");
    if (!enabled) return;
    
    this->amount = amount;
    this->iterations = iterations;
    
    fbo1.begin();
    ofClear(0, 0, 0);
    fbo1.end();
    fbo2.begin();
    ofClear(0, 0, 0);
    fbo2.end();
    
	//start 'recording' the user's drawing commands to the fbo
	fbo1.begin();
}

void ofxBlurShader::end() {
    if (!enabled) return;
        
	fbo1.end();

    for (int i=0; i<iterations; i++) {
        //apply horizontal blur to fbo1 and put the result in fbo2
        fbo2.begin();
        hShader.begin();
        hShader.setUniform1f("blurAmnt", amount);
        fbo1.draw(0,0);
        hShader.end(); 
        fbo2.end();
        
        //apply vertical blur to fbo2 and put this back in fbo1
        fbo1.begin(); 
        vShader.begin(); 
        vShader.setUniform1f("blurAmnt", amount); 
        fbo2.draw(0,0); 
        hShader.end(); 
        fbo1.end();
    }
    
    ofSetColor(255);
    fbo1.draw(0,0);
}

