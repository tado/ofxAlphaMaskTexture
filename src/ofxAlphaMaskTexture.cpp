#include "ofxAlphaMaskTexture.h"

ofxAlphaMaskTexture::ofxAlphaMaskTexture(ofTexture _topLayer, ofTexture _bottomLayer, ofTexture _maskLayer){
    
    frag = STRINGIFY
    (
     uniform sampler2DRect Tex0;
     uniform sampler2DRect Tex1;
     
     void main (void){
         vec4 image = texture2DRect(Tex0, gl_TexCoord[0].st);
         vec4 composite = texture2DRect(Tex1, gl_TexCoord[1].st);
         gl_FragData[0] = vec4(image.rgb,composite.r);
     }
     );
    
    vert = STRINGIFY
    (
     void main(void){
         gl_Position = ftransform();
         gl_TexCoord[0] = gl_MultiTexCoord0;
         gl_TexCoord[1] = gl_MultiTexCoord1;
     }
     );
    
    if (frag.empty() == false) {
        maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
    }
    if (vert.empty() == false) {
        maskShader.setupShaderFromSource(GL_VERTEX_SHADER, vert);
    }
    
    maskShader.linkProgram();
    
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
