#include <RealEngine/physic_core.h>
#include "player.h"
#include <iostream>

Player::Player(re::Point2f pos) 
    : Unit(pos) 
{
    level = 1;
    exp = 0;
    hp = 500;
    maxhp = 500;
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

    //re::subscribe_to_event_type(this, MOVE_EVENT_CATEGORY, (int)MoveEventType::PLAYER_MOVE);
    re::subscribe_to_all( this );
    
    physic_type = PLAYER_PHYSIC_TYPE;

}

void Player::attack() {

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

void Player::display(re::Camera camera){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f screen_pos = camera.world_to_screen(geo_pos); 

    float size = camera.meter_to_screen(50);

    re::draw_image_part(screen_pos.x - size, screen_pos.y - size,
                        screen_pos.x + size, screen_pos.y + size,
                        0, 0, 1, 1,
                        movingAnim_Forward->getNextFrame());
}

void Player::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}


void Player::on_event(std::shared_ptr<re::Event> event) {
    if( event->get_category() == MOVE_EVENT_CATEGORY && event->get_type() == int(MoveEventType::PLAYER_MOVE) ) {
        std::shared_ptr<MoveEvent> move_event = std::static_pointer_cast<MoveEvent>(event);
        if( this->get_id() == move_event->player_id ) {
            go_to(move_event->finish_point);
        }
    }
}