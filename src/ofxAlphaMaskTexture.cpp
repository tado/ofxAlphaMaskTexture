#include "ofxAlphaMaskTexture.h"

ofxAlphaMaskTexture::ofxAlphaMaskTexture(ofTexture _topLayer, ofTexture _bottomLayer, ofTexture _maskLayer){
    
    if(ofIsGLProgrammableRenderer()){
        string vertex = "#version 150\n\
        \n\
        uniform mat4 projectionMatrix;\n\
        uniform mat4 modelViewMatrix;\n\
        uniform mat4 modelViewProjectionMatrix;\n\
        \n\
        \n\
        in vec4  position;\n\
        in vec2  texcoord;\n\
        \n\
        out vec2 texCoordVarying;\n\
        \n\
        void main()\n\
        {\n\
        texCoordVarying = texcoord;\
        gl_Position = modelViewProjectionMatrix * position;\n\
        }";
        string fragment = "#version 150\n\
        \n\
        uniform sampler2DRect tex0;\
        uniform sampler2DRect maskTex;\
        in vec2 texCoordVarying;\n\
        \
        out vec4 fragColor;\n\
        void main (void){\
        vec2 pos = texCoordVarying;\
        \
        vec3 src = texture(tex0, pos).rgb;\
        float mask = texture(maskTex, pos).r;\
        \
        fragColor = vec4( src , mask);\
        }";
        maskShader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
        maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
        maskShader.bindDefaults();
        maskShader.linkProgram();
    }else{
        string shaderProgram = "#version 120\n \
        #extension GL_ARB_texture_rectangle : enable\n \
        \
        uniform sampler2DRect tex0;\
        uniform sampler2DRect maskTex;\
        \
        void main (void){\
        vec2 pos = gl_TexCoord[0].st;\
        \
        vec3 src = texture2DRect(tex0, pos).rgb;\
        float mask = texture2DRect(maskTex, pos).r;\
        \
        gl_FragColor = vec4( src , mask);\
        }";
        maskShader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
        maskShader.linkProgram();
    }

    
    width = ofGetWidth();
    height = ofGetHeight();
    maskFbo.allocate(width,height);
    fbo.allocate(width,height);
    
    topLayer = _topLayer;
    bottomLayer = _bottomLayer;
    maskLayer = _maskLayer;
    
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
}
void ofxAlphaMaskTexture::update(){

}

void ofxAlphaMaskTexture::draw(){
    maskFbo.begin();
    ofClear(0,0,0,255);
    ofSetColor(255,255);
    maskLayer.draw(0, 0, width, height);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    maskShader.begin();
    maskShader.setUniformTexture("maskTex", maskFbo.getTexture(), 1 );
    topLayer.draw(0, 0, width, height);
    maskShader.end();
    fbo.end();

    ofSetColor(255,255);
    bottomLayer.draw(0, 0, width, height);
    fbo.draw(0,0);
}
