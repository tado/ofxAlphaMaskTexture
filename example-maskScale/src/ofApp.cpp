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
    
    gui.setup(); // most of the time you don't need a name
    gui.add(maskScale.setup("Mask Scale", 1.0, 0.0, 3.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    ofSetWindowTitle("frame rate = " + ofToString(ofGetFrameRate(), 2) + "fps");
    alphaMask->maskScale = maskScale;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    alphaMask->draw();
    gui.draw();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
