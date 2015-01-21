#include "ofxAlphaMaskTexture.h"

ofxAlphaMaskTexture::ofxAlphaMaskTexture(ofTexture _topLayer, ofTexture _bottomLayer, ofTexture _maskLayer){
    maskShader.load("../../../../../addons/ofxAlphaMaskTexture/src/shader/composite");
    width = ofGetWidth();
    height = ofGetHeight();
    
    topLayer = _topLayer;
    bottomLayer = _bottomLayer;
    maskLayer = _maskLayer;
    
    maskShader.begin();
    maskShader.setUniformTexture("Tex0", topLayer, 0);
    maskShader.setUniformTexture("Tex1", maskLayer, 1);
    maskShader.end();
}

void ofxAlphaMaskTexture::update(){
    maskShader.setUniformTexture("Tex0", topLayer, 0);
    maskShader.setUniformTexture("Tex1", maskLayer, 1);
}

void ofxAlphaMaskTexture::draw(){
    bottomLayer.draw(0, 0, width, height);
    
    maskShader.begin();
    
    glActiveTexture(GL_TEXTURE0_ARB);
    topLayer.bind();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    maskLayer.bind();
    
    glBegin(GL_QUADS);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
    glVertex2f( 0, 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), 0);
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskLayer.getWidth(), 0);
    glVertex2f( width, 0);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, maskLayer.getWidth(), maskLayer.getHeight());
    glVertex2f( width, height);
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, topLayer.getHeight());
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, maskLayer.getHeight());
    glVertex2f( 0, height );
    
    glEnd();
    
    glActiveTexture(GL_TEXTURE1_ARB);
    maskLayer.unbind();
    
    glActiveTexture(GL_TEXTURE0_ARB);
    topLayer.unbind();
    
    maskShader.end();
}
