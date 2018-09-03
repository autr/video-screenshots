#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    dotSize = 8;
    snapTime = 0.2;
    lastOpened.open("last-opened.txt");
    if (lastOpened.exists()) {
        /* Open and read from data file */
        string line;
        ifstream data;
        data.open(ofToDataPath("last-opened.txt"));
        
        while(!data.eof()){
            getline(data, line);
            string str = line;
            ofLog() << str;
            currentName = ofFilePath::getFileName(str);
            currentName = ofFilePath::removeExt(currentName);
            player.load(str);
            player.play();
            box.set(0,0,player.getWidth(), player.getHeight());

        }
        data.close();
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    
    
}

void ofApp::scrollPlayer(int x, int y) {
    float p = ofMap(x, box.getX(), box.getWidth() + box.getX(), 0, 1, true);
    player.setPosition(p);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofBackground(0);
    if (player.isInitialized()) {
    
        int x = ofMap(player.getPosition(), 0, 1, dotSize, ofGetWidth() - (dotSize * 2));
        
        ofDrawLine(x, dotSize, x, ofGetHeight() - (dotSize * 2));
        
        ofRectangle bounds(dotSize,dotSize, ofGetWidth() - (dotSize * 2), ofGetHeight() - (dotSize * 2));
        box.scaleTo(bounds);
        player.draw(box);
        ofNoFill();
        ofDrawRectangle(box);
        ofFill();
        ofDrawCircle(x, ofGetHeight() - (dotSize * 2), dotSize);
        ofDrawCircle(x, (dotSize * 2), dotSize);
        
        float time = ofGetElapsedTimef();
        if (time <= flashTime) {
            int alpha = ofMap(time, flashTime, flashTime - snapTime, 0, 255, true);
            ofSetColor(255,255,255, alpha);
            ofDrawRectangle(box);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs& e){
    
    int key = e.key;
    
    if (key == ' ') player.setPaused(!player.isPaused());
    if (key == 'c' ) {
        img.setFromPixels(player.getPixels());
        string name = currentName;
        int p = player.getPosition() * 10000;
        float pp = (float)p/(float)100.0;
        name += " ";
        name += ofToString(pp);
        name += "% .jpg";
        flashTime = ofGetElapsedTimef() + snapTime;
        img.save(name, OF_IMAGE_QUALITY_BEST);
    }
    
    if (key == OF_KEY_RIGHT) {
        player.nextFrame();
        if (e.hasModifier(OF_KEY_SHIFT)) for (int i = 0; i < 9; i++) player.nextFrame();
        if (e.hasModifier(OF_KEY_COMMAND)) for (int i = 0; i < 9; i++) player.nextFrame();
        if (e.hasModifier(OF_KEY_CONTROL)) for (int i = 0; i < 9; i++) player.nextFrame();
        if (e.hasModifier(OF_KEY_ALT)) for (int i = 0; i < 9; i++) player.nextFrame();
    }
    if (key == OF_KEY_LEFT) {
        player.previousFrame();
        if (e.hasModifier(OF_KEY_SHIFT)) for (int i = 0; i < 9; i++) player.previousFrame();
        if (e.hasModifier(OF_KEY_COMMAND)) for (int i = 0; i < 9; i++) player.previousFrame();
        if (e.hasModifier(OF_KEY_CONTROL)) for (int i = 0; i < 9; i++) player.previousFrame();
        if (e.hasModifier(OF_KEY_ALT)) for (int i = 0; i < 9; i++) player.previousFrame();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    scrollPlayer(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    scrollPlayer(x, y);
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
    ofBuffer dataBuffer;
    dataBuffer.append(dragInfo.files[0]);
    bool fileWritten = ofBufferToFile("last-opened.txt", dataBuffer);
    currentName = ofFilePath::getFileName(dragInfo.files[0]);
    currentName = ofFilePath::removeExt(currentName);
    player.load(dragInfo.files[0]);
    player.play();
    box.set(0,0,player.getWidth(), player.getHeight());
}
