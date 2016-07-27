#include "ofMain.h"
#include "ofApp.h"
//#include "ofxWatchdog.h"

//========================================================================
int main( ){
   ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(1440,900,OF_FULLSCREEN);			// <-------- setup the GL context

    // ofxWatchdog::watch(msec, reboot, override, verbose)
    //
    //     msec : how long does the watchdog wait, when the process hangs-up in milli seconds
    //   reboot : automatically restart the process
    // override : use internal signal handler (optional)
    //  verbose : print more log information (optional)
    
//    ofxWatchdog::watch(3000, true, true, true);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
