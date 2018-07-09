#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include "player.h"
#include <iostream>

Player::Player(re::Point2f pos) 
    : Unit(pos) 
{
    level = 1;
    exp = 0;
    hp = 500;
    maxhp = 500;

    physic_type = PLAYER_PHYSIC_TYPE;

}
double Player::get_hp(){
    return hp / maxhp * 100;
}

void Player::add_exp(int amount){
    // exp += amount;
    // if ((level != 20) && (exp >= expToNextLevel[level - 1])){
    //     std::cout << "New level!\n";
    //     exp -= expToNextLevel[level - 1];
    //     level++;
    //     maxhp += maxhp * 0.1;
    //     if (level == 20) exp = 0;
    // }
}

void Player::update(){
    Unit::update();
}

void Player::reduceCooldowns(){
    // for (uint i = 0; i < abilities.size(); i++)
        // abilities[i]->reduceCooldown();
}

void Player::load_animation() {
    movingAnim_Forward = std::make_shared<re::Animation>(0.1, true);

    resource_manager.load_file("resource.xml");

    re::ImagePtr image = resource_manager.get_image("player_move1");
    movingAnim_Forward->add_frame(image);
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move2"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move3"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move4"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move5"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move6"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move7"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move8"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move9"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move10"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move11"));
    movingAnim_Forward->add_frame(resource_manager.get_image("player_move12"));
}

void Player::display(re::Camera camera){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f screen_pos = camera.world_to_screen(geo_pos); 

    if( ! movingAnim_Forward ) {
        this->load_animation();
    }

    float size = camera.meter_to_screen(50);

    re::draw_image_part(screen_pos.x - size, screen_pos.y - size,
                        screen_pos.x + size, screen_pos.y + size,
                        0, 0, 1, 1,
                        movingAnim_Forward->getNextFrame());

    if (re::ConfigManager::get_property("common/debug_display") == "1"){
        re::Point2f screen_pos = camera.world_to_screen(goto_point);
        re::draw_rectangle(screen_pos - re::Point2f(5, 5), re::Point2f(10, 10), re::RED);
    }

    draw_fireball( camera );
}

void Player::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}