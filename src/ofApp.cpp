#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowShape(1920, 1080);
    width_ = ofGetWidth();
    height_ = ofGetHeight();
    
//    ofHideCursor();
    
    fbo_.allocate(width_, height_, GL_RGB);
    fbo_.begin();
    ofClear(0, 0, 0, 0);
    fbo_.end();
    
    shader_.load("shader.vert", "shader.frag");
    
    gui_->setup();
    
    //osc 初期化
    utilities_->osc_sender.setup(IP, SEND_PORT);
    utilities_->osc_receiver.setup(RECV_PORT);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    while(utilities_->osc_receiver.hasWaitingMessages()){
        ofxOscMessage recv_m;
        utilities_->osc_receiver.getNextMessage(recv_m);
        
        if(recv_m.getAddress() == "/device"){
            cout << "color " << recv_m.getArgAsInt(4) << ", " << recv_m.getArgAsInt(5) << ", " << recv_m.getArgAsInt(6) << endl;
            recv_color_.r = recv_m.getArgAsInt(4);
            recv_color_.g = recv_m.getArgAsInt(5);
            recv_color_.b = recv_m.getArgAsInt(6);
        
            cout << "pos " << recv_m.getArgAsInt(0) << ", " << recv_m.getArgAsInt(1) << endl;
            ofVec2f touch_pos_;
            touch_pos_.x = ofMap(static_cast<float>(recv_m.getArgAsInt(0)), 0, recv_m.getArgAsInt(2), 0, ofGetWidth());
            touch_pos_.y = ofMap(static_cast<float>(recv_m.getArgAsInt(1)), 0,  recv_m.getArgAsInt(3), 0, ofGetHeight());
            ParSysRef ps = make_shared<ParticleSystem>(touch_pos_, gui_->dot_len_, gui_->draw_rad_, recv_color_);
            ps_vec_.push_back(ps);
        }
        
    }
    
   fbo_.begin();
        for_each(ps_vec_.begin(), ps_vec_.end(), [](ParSysRef ps){ ps->update(); } );
    
        auto end = remove_if(ps_vec_.begin(), ps_vec_.end(), [](ParSysRef ps){ return ps->isDead(); } );
        ps_vec_.erase(end, ps_vec_.end());
    
        if(!ps_vec_.empty())
            for_each(ps_vec_.begin(), ps_vec_.end(), [](ParSysRef ps){ ps->draw(); } );
    fbo_.end();
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader_.begin();
    shader_.setUniformTexture("texture", fbo_, 0);
    shader_.setUniform2f("resolution", width_, height_);
    shader_.setUniform1f("time", ofGetElapsedTimef());
    ofDrawRectangle(0, 0, width_, height_);
    shader_.end();
    
    if(gui_->isHide_) gui_->draw();
    
    stringstream reportStr;
    reportStr << "fps: " << ofGetFrameRate() << endl;
    
    ofFloatColor(1.0, 1.0, 1.0);
    ofDrawBitmapString(reportStr.str(), 20, 20);
    
    utilities_->reportStr.str("");
    utilities_->reportStr << "Clear Press Space Key " << endl;
    ofFloatColor(1.0, 1.0, 1.0);
    ofDrawBitmapString(utilities_->reportStr.str(), 20, height_-50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'f':
        {
            ofVec2f mouse_pos = ofVec2f(static_cast<float>(mouseX), static_cast<float>(mouseY));
            
            ParSysRef ps = make_shared<ParticleSystem>(mouse_pos, gui_->dot_len_, gui_->draw_rad_, gui_->draw_color_);
            ps_vec_.push_back(ps);
            
        }
            break;
            
        case ' ':
        {
            fbo_.begin();
            ps_vec_.clear();
            ofClear(0, 0, 0, 0);
            fbo_.end();
        }
            break;
            
        case 'b':
            gui_->isHide_ = gui_->isHide_ ? false : true;
            break;
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
    ofVec2f mouse_pos = ofVec2f(static_cast<float>(x), static_cast<float>(y));
    
    ParSysRef ps = make_shared<ParticleSystem>(mouse_pos, gui_->dot_len_, gui_->draw_rad_, gui_->draw_color_);
    
    ps_vec_.push_back(ps);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofVec2f mouse_pos = ofVec2f(static_cast<float>(x), static_cast<float>(y));

    ParSysRef ps = make_shared<ParticleSystem>(mouse_pos, gui_->dot_len_, gui_->draw_rad_, gui_->draw_color_);

    ps_vec_.push_back(ps);
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
