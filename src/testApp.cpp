#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	frameByframe = false;

	// Uncomment this to show movies with alpha channels
	// fingerMovie.setPixelFormat(OF_PIXELS_RGBA);

	fingerMovie.loadMovie("https://v.cdn.vine.co/v/videos/17CA24CE-0455-421B-9E6F-5EE25F47B490-77284-0000144C972CE63F_1dbb33a24c5.1.2.mp4");
    reloadCount = 0;
	fingerMovie.play();
}


//--------------------------------------------------------------
void testApp::draw(){

	ofSetHexColor(0xFFFFFF);

    fingerMovie.draw(20,20);
    ofSetHexColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    
//    int nChannels = fingerMovie.getPixelsRef().getNumChannels();
//    
//    // let's move through the "RGB(A)" char array
//    // using the red pixel to control the size of a circle.
//    for (int i = 4; i < 320; i+=8){
//        for (int j = 4; j < 240; j+=8){
//            unsigned char r = pixels[(j * 320 + i)*nChannels];
//            float val = 1 - ((float)r / 255.0f);
//            ofCircle(400 + i,20+j,10*val);
//        }
//    }


    ofSetHexColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetHexColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);
    
    ofDrawBitmapString("reloadCount: " + ofToString(reloadCount,2) + " elapsedTime: " + ofToString(ofGetElapsedTimef(),2),20,440);
    
    if(fingerMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
            
        case 'l':
            fingerMovie.loadMovie("https://v.cdn.vine.co/v/videos/17CA24CE-0455-421B-9E6F-5EE25F47B490-77284-0000144C972CE63F_1dbb33a24c5.1.2.mp4");
        break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//	if(!frameByframe){
//        fingerMovie.setPaused(true);
//	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    float randVal = ofRandom(1);
    string loadStr;
    ofVideoPlayer myNewPlayer;
    if(randVal < .33333)
    {
        loadStr = "https://v.cdn.vine.co/v/videos/E4A9EC7D-0BC4-4B65-8420-03184DABBE9B-1518-0000009CD00FBF18_1.1.2.mp4";
    }
    else if (randVal < .666)
    {
        loadStr ="https://v.cdn.vine.co/v/videos/17CA24CE-0455-421B-9E6F-5EE25F47B490-77284-0000144C972CE63F_1dbb33a24c5.1.2.mp4";
    }
    else
    {
        loadStr ="movies/fingers.mov";
    }
     cout << "loading... "  << loadStr << endl;
    myNewPlayer.loadMovie(loadStr);
    fingerMovie.close();
    fingerMovie = myNewPlayer;
    fingerMovie.play();
    reloadCount++;
    cout << "done, " << endl;
    cout << "reloadCount: " << reloadCount  << "[" << ofGetElapsedTimef() << "]" << endl;
    //qtmoviekit dealloc - if(ofRandom(1.f) < .05)
    //debug: 62,124,37,53,299,23, 64,37,33,1,45,72,45[18.8979],184[69.4916],32[17.6917],16[5.53028],125[53.5079],16[5.7133],26[12.5073],31[14.4164],196[89.5074],180[70.4979],79[32.5106],65[26.1172]
    
    //qtmoviekit dealloc - if(ofRandom(1.f) > .05)
    //debug: 269,135,231,1943,1677[136.962]
    
    //qtmoviekit dealloc/close - myNewPlayer+ (ofRandom(1.f) < .05)
    //673[242.441],858[319.017],235[93.1933],940[261.76],2355[870.25],1132[387.621],1346[482.081]

    //qtmoviekit dealloc/close - myNewPlayer+ (ofRandom(1.f) > .05)
    //673[242.441],858[319.017],235[93.1933],940[261.76],2355[870.25],1132[387.621],1346[482.081]
    
    //qtmoviekit dealloc/close - myNewPlayer+ (ofRandom(1.f) < .02)
    //710[238.63],157[28.257],779[610.05],55[56.3435]
}


//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.update();
    if(ofRandom(1.f) < .02)
    {
        mouseReleased(0,0,0);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
