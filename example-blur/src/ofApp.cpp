#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // setup Blur (ofxBlurFilter)
    blur.setup(ofGetWidth(), ofGetHeight());
    
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    maskFbo.allocate(ofGetWidth(), ofGetHeight());
    maskFbo.begin();
    ofClear(0, 0, 0);
    maskFbo.end();
    
    bottomImg.load("space.jpg");
    
    alphaMask = new ofxAlphaMaskTexture(cam.getTexture(),        // top layer texture
                                        bottomImg.getTexture(),  // bottom layer texture
                                        maskFbo.getTexture());   // mask layer texture
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    ofSetWindowTitle("frame rate = " + ofToString(ofGetFrameRate(), 2) + "fps");
}

//--------------------------------------------------------------
void ofApp::draw(){
    float blurAmount = ofMap(mouseX, 0, ofGetWidth(), 0, 10.0);

    // draw mask int FBO
    maskFbo.begin();
    blur.begin(blurAmount, 10); // blur begin
    ofSetCircleResolution(64);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight(), ofGetHeight());
    blur.end(); // blur end
    maskFbo.end();
    
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
