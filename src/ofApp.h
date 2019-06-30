#pragma once

#include "ofMain.h"
#include "ofxVideoRecorder.h"

//FileSaver
#include "ofxJSONElement.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioIn(float * input, int bufferSize, int nChannels);
	
	//Subtitles Functions
	string formatSubtitleTimeStamp(int hour, int minute, int second, int milisecond);
	void startSaveSubtitles();
	void addOneSubtitle(int idVideo, string description);
	void endSaveSubtitlesFile();
    
    ofVideoGrabber      vidGrabber;
    ofxVideoRecorder    vidRecorder;
    ofSoundStream       soundStream;
    bool bRecording;
    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
	
	
    ofFbo recordFbo;
    ofPixels recordPixels;
	
	//Save some Info (TAG) in a json
	ofxJSONElement resultJson;
	ofFile mySubtitlesTextFile;
	int counterVideos = 0;
	int counterSubtitles = 0;
	long initTimeVideo = 0;
	string timeStamp_init_subtitle = "00:00:00,000";
	string timeStamp_end_subtitle = "00:00:00,000";
	int secondsSubtitleVisible = 2;

};
