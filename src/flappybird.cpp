#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <vector>
#include <RealEngine/math.h>

#include <iostream>

#include "flappybird.h"

void FlappyBird::setup() {
    SpeedY_ = 3;
    ColumnsSpeed_ = 3;
    X_ = flappy_bird_size / 3;
    height_ = 250;
    frame_ = 0;
    column_score_ = 0;
    acceler_ = 1;
    BirdY_ = flappy_bird_size / 2;
    BirdX_ = flappy_bird_size / 2;
    goUP_ = false;
    gameover_ = false;
    score_ = 0;
    bestscore_ = 0;
    columns_height_.push_back(height_);
    columnsX_.push_back(X_);
}

void FlappyBird::update() {
    if(gameover_ == true){
        if(BirdY_ + 40 >= flappy_bird_size)
            BirdY_ = flappy_bird_size - 40;
    }
    else if(BirdY_ + 40 >= flappy_bird_size){
        gameover_ = true;
    }
    
    if(gameover_ == false){
        frame_++;
        for(size_t i = 0; i < columnsX_.size(); i++){
            if((columnsX_[i] <= BirdX_ + 40 && columnsX_[i] + flappy_bird_size / 10 >= BirdX_) 
            && (BirdY_ <= columns_height_[i] + 30 || BirdY_ + 40 >= columns_height_[i] + 190)){
                BirdX_ = BirdX_ - 30;
                BirdY_ = BirdY_ - 30;
                gameover_ = true;
            }
        }
        for(size_t i = 0; i < columnsX_.size(); i++){
            if(columnsX_[i] + flappy_bird_size / 10 == flappy_bird_size / 2 - ColumnsSpeed_)
                score_++;
        }
        if(BirdY_ > 0){
            if(SpeedY_ > 0 && goUP_ == true){
                frame_ = 0;
                SpeedY_ = -6;
            }
            else if(frame_ == 15 && goUP_ == true){
                SpeedY_ = 3;
                goUP_ = false;
                frame_ = 0;
            }
        }
        else{
            SpeedY_ = 3;
            goUP_ = false;
        }
        if(frame_ % 5 == 0 && goUP_ == false)
            SpeedY_ += acceler_;
        if(columnsX_.back() <= flappy_bird_size / 2){
            columns_height_.push_back(rand() % (flappy_bird_size / 2));
            columnsX_.push_back(flappy_bird_size);
        }
        for(size_t i = 0; i < columnsX_.size(); i++){
            columnsX_[i] -= ColumnsSpeed_;
        }
    }
    BirdY_ += SpeedY_;
}

void FlappyBird::display() {
    for(size_t i = 0; i < columnsX_.size(); i++){
        re::draw_rectangle(columnsX_[i], 0, flappy_bird_size / 10, columns_height_[i] + 30, re::GREEN);
        re::draw_rectangle(columnsX_[i], columns_height_[i] + 190, flappy_bird_size / 10,
        flappy_bird_size - (columns_height_[i] + 190), re::GREEN);
    }
    re::draw_rectangle(BirdX_, BirdY_, 40, 40, re::RED);
    re::draw_line(BirdX_ + 10, BirdY_ + 40, BirdX_ + 10, BirdY_ + 50, re::RED);
    re::draw_line(BirdX_ + 30, BirdY_ + 40, BirdX_ + 30, BirdY_ + 50, re::RED);
    re::draw_line(BirdX_, BirdY_ + 20, BirdX_ - 20, BirdY_ + 15, re::BLACK);
    re::draw_line(BirdX_, BirdY_ + 20, BirdX_ - 20, BirdY_ + 20, re::BLACK);
    re::draw_line(BirdX_, BirdY_ + 20, BirdX_ - 20, BirdY_ + 25, re::BLACK);
    if(goUP_ == false){
        re::draw_line(BirdX_ + 5, BirdY_ + 5, BirdX_ + 20, BirdY_ - 10, re::BLACK);
        re::draw_line(BirdX_ + 25, BirdY_ + 5, BirdX_ + 20, BirdY_ - 10, re::BLACK);
    }
    else{
        re::draw_line(BirdX_ + 5, BirdY_ + 5, BirdX_ + 20, BirdY_ + 30, re::BLACK);
        re::draw_line(BirdX_ + 25, BirdY_ + 5, BirdX_ + 20, BirdY_ + 30, re::BLACK);
    }
    re::draw_line(BirdX_ + 40, BirdY_ + 10, BirdX_ + 60, BirdY_ + 20, re::RED);
    re::draw_line(BirdX_ + 40, BirdY_ + 30, BirdX_ + 60, BirdY_ + 20, re::RED);
    re::draw_line(BirdX_ + 30, BirdY_ + 5, BirdX_ + 35, BirdY_ + 10, re::BLACK);
    re::background(re::BLUE);
    if(gameover_ == true){
        re::draw_line(BirdX_ + 30, BirdY_ + 10, BirdX_ + 35, BirdY_ + 5, re::BLACK);
        SpeedY_ = 3;
        re::draw_text(flappy_bird_size / 6, flappy_bird_size / 2 + 10,
        std::string("GAME OVER! Press R to play a new game."), re::Color(re::BLACK));
    }
    re::draw_text(50, flappy_bird_size / 10 - 10, std::string("BEST SCORE:"), re::Color(re::BLACK));
    re::draw_text(225, flappy_bird_size / 10 - 10, std::to_string(bestscore_), re::Color(re::BLACK));
    re::draw_text(350, flappy_bird_size / 10 - 10, std::string("SCORE:"), re::Color(re::BLACK));
    re::draw_text(460, flappy_bird_size / 10 - 10, std::to_string(score_), re::Color(re::BLACK));
}   

void FlappyBird::on_key_pressed(re::Key key){
    if (key == re::Key::Escape){
        re::exitApp();
    } 
    if(key == re::Key::Up) {
        if(gameover_ == false)
            goUP_ = true; 
    }
    if(key == re::Key::W) {
        if(gameover_ == false)
            goUP_ = true; 
    }
    if(key == re::Key::R){
        gameover_ = false;
        if(bestscore_ < score_)
            bestscore_ = score_;
        score_ = 0;
        column_score_ = 0;
        BirdY_ = flappy_bird_size / 2;
        BirdX_ = flappy_bird_size / 2;
        ColumnsSpeed_ = 3;
        columnsX_.clear();
        columns_height_.clear();
        columnsX_.push_back(X_);
        columns_height_.push_back(height_);
    }
}
