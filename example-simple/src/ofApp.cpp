#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    
    bottomImg.load("space.jpg");
    maskImg.load("mask.jpg");
    
    alphaMask = new ofxAlphaMaskTexture(cam.getTexture(),        // top layer texture
                                        bottomImg.getTexture(),  // bottom layer texture
                                        maskImg.getTexture());   // mask layer texture
    
    alphaMask->maskScale = 1.2; //Mask Layer Scale (default = 1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    ofSetWindowTitle("frame rate = " + ofToString(ofGetFrameRate(), 2) + "fps");
    alphaMask->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
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
