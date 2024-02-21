#pragma once

#include "ofMain.h"
#include "Gui.hpp"
#include "Utilities.h"

#include "ParticleSystem.hpp"

typedef shared_ptr<ParticleSystem> ParSysRef;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Gui* gui_ = Gui::getInstance();
    Utilities* utilities_ = Utilities::getInstance();
    
    int width_;
    int height_;
    
    ofFbo fbo_;
    ofShader shader_;
    
    vector<ParSysRef> ps_vec_;
    ofColor recv_color_;
    
};
