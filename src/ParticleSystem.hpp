//
//  ParticleSystem.hpp
//  DrawingParticle
//
//  Created by 白井　 大地 on 2018/12/07.
//

#pragma once

#include "ofMain.h"
#include "Utilities.h"
#include "Gui.hpp"

class Particle : public ofBaseApp{
private:
    int16_t life_;
    int16_t max_life_;
    ofVec2f mouse_pos_;
    ofVec2f velocity_1_;
    ofVec2f velocity_2_;
    ofVec2f acceleration_;
    float   angle_;
    float   mass_;      //パーティクルの円のサイズ
    float   gravity_;
    ofVec2f draw_pos_;
    float   draw_rad_; //飛び散る範囲の半径
    float   cur_time_f_;
    enum EDotSize {
        DOT_SIZE_S,
        DOT_SIZE_M,
        DOT_SIZE_L
    }dot_size_;
    
    Gui* gui_ = Gui::getInstance();
    
public:
    Particle(int16_t _life, ofVec2f _mouse_pos, float _angle, float _draw_rad, float _cur_time_f):
    life_(_life),
    mouse_pos_(_mouse_pos),
//    velocity_1_(ofVec2f(ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f))),
    acceleration_(ofVec2f(2.f, 2.f)),
    angle_(_angle),
    gravity_(9.8),
    draw_rad_(_draw_rad),
    cur_time_f_(_cur_time_f)
    {
        max_life_ = life_;
        
//        velocity_2_ = velocity_1_;
        float rand = ofRandom(0.f, 1.f);
        if(rand < 0.2)      dot_size_ = DOT_SIZE_L;
        else if(rand < 0.5) dot_size_ = DOT_SIZE_M;
        else                dot_size_ = DOT_SIZE_S;
        
//        dot_size_ = DOT_SIZE_L;
        switch(dot_size_){
            case DOT_SIZE_S:
            {
                mass_ = ofRandom(0.001f, 1.f);
                float VAL = gui_->coefficient_S_;

                draw_pos_.x = mouse_pos_.x + cos(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(cos(angle_))*cur_time_f_)*ofRandom(70, 100);
                draw_pos_.y = mouse_pos_.y + sin(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(sin(angle_))*cur_time_f_)*ofRandom(70, 100);
                
            }
                break;

            case DOT_SIZE_M:
            {
                mass_ = ofRandom(2.f, 3.5f);
                float VAL = gui_->coefficient_M_;
                
                draw_pos_.x = mouse_pos_.x + cos(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(cos(angle_))*cur_time_f_)*ofRandom(30, 100);
                draw_pos_.y = mouse_pos_.y + sin(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(sin(angle_))*cur_time_f_)*ofRandom(30, 100);
                
                float rand2 = ofRandom(0.f, 1.f);
                if(rand < 0.03) life_ = ofRandom(40, 60);
                else           life_ = 20;
                max_life_ = life_;
            }
                break;

            case DOT_SIZE_L:
            {
                float VAL = gui_->coefficient_L_;
                mass_ = ofRandom(8.f, 15.f);
                
                draw_pos_.x = mouse_pos_.x + cos(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(cos(angle_))*cur_time_f_)*30;
                draw_pos_.y = mouse_pos_.y + sin(angle_)*(draw_rad_/VAL) + ofSignedNoise(ofRandom(sin(angle_))*cur_time_f_)*30;
                
                float rand2 = ofRandom(0.f, 1.f);
                if(rand < 0.008) life_ = ofRandom(30, 50);
                else           life_ = 20;
                max_life_ = life_;
            }
                break;
        }
        
        if(draw_pos_.x > _mouse_pos.x) velocity_1_.x = abs(ofSignedNoise(ofRandom(cos(angle_)*cur_time_f_)));
        else                           velocity_1_.x = abs(ofSignedNoise(ofRandom(cos(angle_)*cur_time_f_)))*-1.f;
        if(draw_pos_.y > _mouse_pos.y) velocity_1_.y = abs(ofSignedNoise(ofRandom(sin(angle_)*cur_time_f_)));
        else                           velocity_1_.y = abs(ofSignedNoise(ofRandom(sin(angle_)*cur_time_f_)))*-1.f;
        
        velocity_2_ = velocity_1_;
    };
    
    ~Particle(){};

    
    void update();
    void draw();
    
    bool isDead() const {
        if(life_ < 0) return true;
        else          return false;
    }
    
};






typedef shared_ptr<Particle> ParticleRef;

class ParticleSystem : public ofBaseApp{
private:
    vector<ParticleRef> particles_;
    
    ofVec2f mouse_pos_;
    int     len_;
    ofColor color_;
    float draw_rad_;
    
    ofSoundPlayer se_;
    
    Gui* gui_ = Gui::getInstance();
    
    void addParticle(int16_t _life, float _angle, float _draw_rad, float _cur_time_f);
    
public:
    
    explicit ParticleSystem(ofVec2f _mpos, int _len, float _draw_rad,const ofColor& _color):
    mouse_pos_(_mpos),
    len_(_len),
    draw_rad_(_draw_rad),
    color_(_color)
    {
        se_.load("sound_03.mp3");
        se_.play();
        float cur_time_f = ofGetElapsedTimef();
        for(int i=0; i<len_; i++){
            addParticle(ofRandom(5, 20), static_cast<float>(i%360), draw_rad_, cur_time_f);
        }
    };
    
    ~ParticleSystem(){};
    
    void update();
    void draw();
    
    void clear(){
        particles_.clear();
    }
    
    bool isDead()const{
        if(particles_.empty()) return true;
        else                   return false;
    }
    
    void setColor(const ofColor& _color){ color_ = _color; }
};
