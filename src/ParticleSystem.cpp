//
//  ParticleSystem.cpp
//  DrawingParticle
//
//  Created by 白井　 大地 on 2018/12/07.
//

#include "ParticleSystem.hpp"

//--------------------------------------------------------------
void Particle::update(){
    if(gui_->isAnimation_){
        ofVec2f damping = ofVec2f(gui_->damping_->x, gui_->damping_->y);
        
        if(life_ >= max_life_ - gui_->poping_frames_){
            velocity_2_ *= acceleration_;
            velocity_2_  = velocity_2_*damping;
            draw_pos_ += velocity_2_;
        }
        else{
            velocity_1_ *= damping;
            draw_pos_   += velocity_1_;
            draw_pos_.y += gui_->g_*sqrt(mass_);
        }
        
    }
    life_ -= 1;
    
}

//--------------------------------------------------------------
void Particle::draw(){
//    ofDrawCircle(draw_pos_.x, draw_pos_.y, mass_);
    
    if(life_ >= 5){
        ofDrawCircle(draw_pos_.x, draw_pos_.y, mass_);
    }
    else{
        switch(dot_size_){
            case DOT_SIZE_S:
                mass_ *= 0.7;
                ofDrawCircle(draw_pos_.x, draw_pos_.y, mass_);
                break;

            case DOT_SIZE_M:
                mass_ *= 0.7;
                ofDrawCircle(draw_pos_.x, draw_pos_.y, mass_);
                break;

            case DOT_SIZE_L:
                mass_ *= 0.1;
                ofDrawCircle(draw_pos_.x, draw_pos_.y, mass_);
                break;
        }
    }
    
}

//--------------------------------------------------------------
void ParticleSystem::update(){
    for_each(particles_.begin(), particles_.end(), [](ParticleRef& p){ p->update(); } );
    
    auto end = remove_if(particles_.begin(), particles_.end(), [](ParticleRef& p){ return p->isDead(); } );
    particles_.erase(end, particles_.end());
}

//--------------------------------------------------------------
void ParticleSystem::draw(){
    ofSetColor(color_);
    for_each(particles_.begin(), particles_.end(), [](ParticleRef& p){ p->draw(); } );
}

//--------------------------------------------------------------
void ParticleSystem::addParticle(int16_t _life,float _angle, float _draw_rad, float _cur_time_f){
    
    ParticleRef p = make_shared<Particle>(_life, mouse_pos_, _angle, _draw_rad, _cur_time_f);
    particles_.push_back(p);

}
