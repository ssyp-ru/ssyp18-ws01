#include <RealEngine/physic_core.h>
#include "player.h"
#include <iostream>

Player::Player(re::Point2f pos) 
    : DrawableGameObject(pos) 
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

    re::subscribe_to_event_type(this, MOVE_EVENT_CATEGORY, (int)MoveEventType::PLAYER_MOVE);
}

// void Player::tryCast(int abilityIndex){
    // if ((abilityIndex < 0) || ((uint)abilityIndex >= abilities.size())) return;
    // if ((abilities[abilityIndex]->getRequiredLevel() <= level) && (abilities[abilityIndex]->canCast())){
        // abilities[abilityIndex]->cast();
    // }
// }

/*void Player::increaseHP(){
    int i;
    if (i > 100) {
        i = 0;
        hp += 1;
    }
    i += increase_speed;
}*/

int Player::getLevel() { return level; }

void Player::addExp(int amount){
    exp += amount;
    if ((level != 20) && (exp >= expToNextLevel[level - 1])){
        std::cout << "New level!\n";
        exp -= expToNextLevel[level - 1];
        level++;
        maxhp += maxhp * 0.1;
        if (level == 20) exp = 0;
    }
}

void Player::update(){
    re::Point2f pos(position.x, position.y);
    if (pos.distance_to(goto_point) < 50)
        velosity = re::Point2f(0,0);
    position.x += velosity.x;
    position.y += velosity.y;
}

void Player::reduceCooldowns(){
    // for (uint i = 0; i < abilities.size(); i++)
        // abilities[i]->reduceCooldown();
}

void Player::display(re::Camera camera){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f screen_pos = camera.world_to_screen(geo_pos); 

    float size = camera.meter_to_screen(50);

    re::draw_image_part(screen_pos.x, screen_pos.y,
                        400, 600,
                        0, 0, 1, 1,
                        movingAnim_Forward->getNextFrame());
}

void Player::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}

void Player::go_to(re::Point2f finish_point){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f vel((finish_point - geo_pos).x, (finish_point - geo_pos).y);

    // setVelocity(vel);
    velosity = finish_point - geo_pos;
    velosity.normalize();
    velosity *= 50;

    goto_point = finish_point;
}


void Player::on_event(std::shared_ptr<re::Event> event) {
    std::shared_ptr<MoveEvent> move_event = std::static_pointer_cast<MoveEvent>(event);
    // std::cout << "Player::on_event, points: " << move_event->finish_point_.x << "\n";
    go_to(move_event->finish_point);
}