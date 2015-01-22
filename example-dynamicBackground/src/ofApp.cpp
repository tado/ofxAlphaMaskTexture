#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(64);
    ofEnableAlphaBlending();
    
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    bgFbo.allocate(ofGetWidth(), ofGetHeight());

    maskImg.loadImage("mask.jpg");
    
    for (int i = 0; i < NUM; i++) {
        location[i] = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        velocity[i] = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
        radius[i] = ofRandom(20, 180);
        color[i].setHsb(ofRandom(255), 255, 255, 100);
    }
    
    alphaMask = new ofxAlphaMaskTexture(cam.getTextureReference(),      // top layer texture
                                        bgFbo.getTextureReference(),    // bottom layer texture
                                        maskImg.getTextureReference()); // mask layer texture
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if (cam.isFrameNew()) {
        alphaMask->update();
    }
    ofSetWindowTitle("framerate = " + ofToString(ofGetFrameRate(), 2) + "fps");
}

//--------------------------------------------------------------
void ofApp::draw(){
    bgFbo.begin();
    {
        ofClear(0);
        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        for (int i = 0; i < NUM; i++) {
            location[i] += velocity[i];
            ofSetColor(color[i]);
            ofCircle(location[i], radius[i]);
            if (location[i].x < 0 || location[i].x > ofGetWidth()) {
                velocity[i].x *= -1;
            }
            if (location[i].y < 0 || location[i].y > ofGetHeight()) {
                velocity[i].y *= -1;
            }
        }
        ofPopStyle();
    }
    bgFbo.end();

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