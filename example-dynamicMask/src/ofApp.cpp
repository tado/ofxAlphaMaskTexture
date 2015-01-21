#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(64);
    ofEnableAlphaBlending();
    
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i < NUM; i++) {
        location[i] = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        velocity[i] = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
        radius[i] = ofRandom(2, 50);
    }
    
    bottomImg.loadImage("space.jpg");
    
    alphaMask = new ofxAlphaMaskTexture(cam.getTextureReference(),       // top layer texture
                                        bottomImg.getTextureReference(), // bottom layer texture
                                        fbo.getTextureReference());      // mask layer texture
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if (cam.isFrameNew()) {
        alphaMask->update();
    }
    ofSetWindowTitle("frame rate = " + ofToString(ofGetFrameRate(), 2) + "fps");
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    {
        ofClear(0);
        ofSetColor(255);
        for (int i = 0; i < NUM; i++) {
            location[i] += velocity[i];
            ofCircle(location[i], radius[i]);
            if (location[i].x < 0 || location[i].x > ofGetWidth()) {
                velocity[i].x *= -1;
            }
            if (location[i].y < 0 || location[i].y > ofGetHeight()) {
                velocity[i].y *= -1;
            }
        }
    }
    fbo.end();

    ofSetColor(255);
    alphaMask->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}