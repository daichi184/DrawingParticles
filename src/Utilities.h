//
//  Utilities.h
//  fogShooter
//
//  Created by 白井　 大地 on 2018/01/10.
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

//#define IP  "127.0.0.1"
#define IP  "192.168.100.57" //アカリ
//#define IP  "192.168.2.110"    //実家

#define SEND_PORT 2346
#define RECV_PORT 2345

class Utilities{
private:
    Utilities(){};
    ~Utilities(){};
    Utilities& operator=(const Utilities&){ return *this; };
    
public:
    static Utilities* getInstance(){
        static Utilities obj;
        return &obj;
    }
    
    int width_ = ofGetWidth(), height_ = ofGetHeight();
    
    ofTrueTypeFont font;
    stringstream   reportStr;
    stringstream   log;
    
    ofxOscSender   osc_sender;
    ofxOscReceiver osc_receiver;
    
};
