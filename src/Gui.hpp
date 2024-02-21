//
//  Gui.hpp
//  PataPataLight
//
//  Created by 白井　 大地 on 2018/09/04.
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Utilities.h"

class Gui : public ofBaseApp{
private:
    Gui(){};
    ~Gui(){};
    Gui& operator=(const Gui&){ return *this; };
    
public:
    static Gui* getInstance(){
        static Gui obj;
        return &obj;
    }
    
    void setup(){
        isHide_ = true;
        gui_.setup();
        gui_.add(draw_color_.setup("draw_color", ofColor(0, 255, 0), ofColor(0, 0, 0), ofColor(255, 255, 255) ));
        gui_.add(poping_frames_.setup("poping_frames", 5, 0, 15));
        gui_.add(dot_len_.setup("dot_len", 325, 1, 5000));
        gui_.add(draw_rad_.setup("draw_rad", 28.85, 10.f, 300.f));
        gui_.add(coefficient_S_.setup("coefficient_S", 0.845, 0.1f, 15.f));
        gui_.add(coefficient_M_.setup("coefficient_M", 32.2855f, 0.1f, 50.f));
        gui_.add(coefficient_L_.setup("coefficient_L", 14.031f,  0.1f, 15.f));
        gui_.add(damping_.setup("damping", ofVec2f(0.9f, 0.9f), ofVec2f(0.f, 0.f), ofVec2f(1.f, 1.f)));
        gui_.add(g_.setup("g", 0.1f,  0.f, 1.f));
        gui_.add(isAnimation_.setup("isAnimation", true));
    }
    
    void draw(){
        
        
        gui_.draw();
        
    }
    
    bool            isHide_;
    ofxPanel        gui_;
    ofxColorSlider  draw_color_;
    ofxIntSlider    dot_len_;
    ofxFloatSlider  draw_rad_; //飛び散る描画半径
    ofxFloatSlider  coefficient_S_;
    ofxFloatSlider  coefficient_M_;
    ofxFloatSlider  coefficient_L_;
    ofxVec2Slider   damping_;
    ofxFloatSlider  g_;
    ofxToggle       isAnimation_;
    ofxIntSlider    poping_frames_;
};
















