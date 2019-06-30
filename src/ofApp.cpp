#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 44100;
    channels = 2;

    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(1920, 1080);
#ifdef TARGET_WIN32
	vidRecorder.setFfmpegLocation("C:\\ffmpeg\\bin\\"); // use this is you have ffmpeg installed in your data folder
#endif
    fileName = "testMovie";
    fileExt = ".mp4"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats

    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    vidRecorder.setVideoCodec("mpeg4"); 
    vidRecorder.setVideoBitrate("800k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");

//    soundStream.listDevices();
//    soundStream.setDeviceID(11);
    soundStream.setup(this, 0, channels, sampleRate, 256, 4);

    ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight()	);
    bRecording = false;
    ofEnableAlphaBlending();
}

void ofApp::exit() {
    vidRecorder.close();
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    if(vidGrabber.isFrameNew() && bRecording){
        bool success = vidRecorder.addFrame(vidGrabber.getPixelsRef());
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }
    
    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (vidRecorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }
    
    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    vidGrabber.draw(0,0);

    stringstream ss;
    ss << "video queue size: " << vidRecorder.getVideoQueueSize() << endl
    << "audio queue size: " << vidRecorder.getAudioQueueSize() << endl
    << "FPS: " << ofGetFrameRate() << endl
    << (bRecording?"pause":"start") << " recording: r" << endl
    << (bRecording?"close current video file: c":"") << endl;

    ofSetColor(0,0,0,100);
    ofRect(0, 0, 260, 75);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ss.str(),15,15);

    if(bRecording){
    ofSetColor(255, 0, 0);
    ofCircle(ofGetWidth() - 20, 20, 5);
    }
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//-------------------------------------
void ofApp::startSaveSubtitles(){
	cout << " ::::::::: bRecording && !vidRecorder.isInitialized() :::::::::" << endl;
	
	if(true){resultJson.clear();
}
	if(true){
		mySubtitlesTextFile.open(fileName+ofGetTimestampString() +".srt",ofFile::WriteOnly);
	}
	
	
	int actualVideoFrame = 0;
	counterVideos++;
	counterSubtitles = 0;
	initTimeVideo = ofGetElapsedTimeMillis();

}

//-----------------------------------------
string ofApp::formatSubtitleTimeStamp(int _hour, int _min, int _sec, int _milis){
	
	int n_zero = 2;
	string old_hour = ofToString(_hour);
	std::string new_hour = std::string(n_zero - old_hour.length(), '0') + old_hour;
	
	string old_minute = ofToString(_min);
	std::string new_minute = std::string(n_zero - old_minute.length(), '0') + old_minute;
	
	string old_second = ofToString(_sec);
	std::string new_second = std::string(n_zero - old_second.length(), '0') + old_second;
	
	n_zero = 3;
	string old_milisecond = ofToString(_milis);	
	std::string new_milisecond = std::string(n_zero - old_milisecond.length(), '0') + old_milisecond;
	
	string resultTimeStampSub = new_hour+":"+new_minute+":"+new_second+","+new_milisecond;
	
	return resultTimeStampSub;
}

//--------------------------------------------------------------
void ofApp::addOneSubtitle(int idVideo, string description) {
	if(true){
		cout << " ::::::::: add 1 FLAG !:::::::::" << endl;
		resultJson[ofToString(idVideo, 2)]["flag"]["videoFrame"] = ofToString(ofToString(counterVideos, 2), 2);
		resultJson[ofToString(idVideo, 2)]["flag"]["descripcion"] = description;
	}

	if(true){
		//Same as json method in txt
		//mySubtitlesTextFile << ofToString(idVideo, 0)+"\n";
		//mySubtitlesTextFile << description + "\n";
		//mySubtitlesTextFile << "\n";
		//If it's necessary do this one the memory, use ofBuffer then safve at the end. https://openframeworks.cc/documentation/utils/ofFile/
		
		//Save str format
		//id counter[1..X]
		counterSubtitles++;
		mySubtitlesTextFile << ofToString(counterSubtitles, 0)+"\n";
		//init time(hh:mm:ss,mss) --> end time(hh:mm:ss,mss)
		//int hourVid;
		//int minVid;
		//int secVid;
		int millisVid;
		long actualTimeVid = ofGetElapsedTimeMillis() - initTimeVideo;
		cout << "actualTimeVid = " << actualTimeVid << endl;
		//https://stackoverflow.com/questions/50727304/convert-milliseconds-to-hoursminutessecondsmilliseconds-in-c
		long milli = actualTimeVid;
		//3600000 milliseconds in an hour
		long hourVid = milli / 3600000;
		milli = milli - 3600000 * hourVid;
		//60000 milliseconds in a minute
		long minVid = milli / 60000;
		milli = milli - 60000 * minVid;
		//1000 milliseconds in a second
		long secVid = milli / 1000;
		milli = milli - 1000 * secVid;
		millisVid = milli;
		
		cout << hourVid << " hours and " << minVid << " minutes and " << secVid << " seconds and " << milli << " milliseconds." << endl;
		
		//timeStamp_init_subtitle = formatSubtitleTimeStamp(0,1,15,300); //example
		timeStamp_init_subtitle = formatSubtitleTimeStamp(hourVid,minVid,secVid,millisVid); //example
		timeStamp_end_subtitle = formatSubtitleTimeStamp(hourVid,minVid,secVid+secondsSubtitleVisible,millisVid);
		
		mySubtitlesTextFile << timeStamp_init_subtitle+" "+"-->"+" "+timeStamp_end_subtitle+"\n";
		//Text with severa end lines ("\n") if it's necesary
		mySubtitlesTextFile << description + "\n";
		mySubtitlesTextFile << "\n";
		
		
	}
	
}


//-------------------------------------
void ofApp::endSaveSubtitlesFile(){
	if(true){
		resultJson.save(fileName+ofGetTimestampString() + ".json", true);
	}
	
	if(true){
		mySubtitlesTextFile.close();
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key=='r'){
        bRecording = !bRecording;
        if(bRecording && !vidRecorder.isInitialized()) {
            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels);
//          vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, vidGrabber.getWidth(), vidGrabber.getHeight(), 30);
//            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
//          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
            
            // Start recording
            vidRecorder.start();
			
			//Save File subtitles
			startSaveSubtitles();
        }
        else if(!bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(true);
        }
        else if(bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(false);
        }
    }
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
		
		//subtitles
		endSaveSubtitlesFile();
    }
	
	if (key == 'f') { // adding one subtitle
		int actualVideoFrame = vidRecorder.getNumVideoFramesRecorded();
		addOneSubtitle(actualVideoFrame, "bla bla bla line1\nblo blo blo line 2");
	}
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
