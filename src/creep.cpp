#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include "creep.h"
#include <iostream>

Creep::Creep(re::Point2f pos, Side side, Line line) 
    : Unit(pos) 
{
    hp = 500;
    maxhp = 500;

    physic_type = CREEP_PHYSIC_TYPE;

    this->side = side;
    switch (line)
    {
        case Line::TOP:
            waypath.addWaypoint(re::Point2f(300, 4000));
            waypath.addWaypoint(re::Point2f(500, 500));
            waypath.addWaypoint(re::Point2f(4000, 300));
            break;
        case Line::MID:
            waypath.addWaypoint(re::Point2f(1000, 4000));
            waypath.addWaypoint(re::Point2f(4000, 1000));
            break;
        case Line::BOT:
            waypath.addWaypoint(re::Point2f(1000, 4700));
            waypath.addWaypoint(re::Point2f(4500, 4500));
            waypath.addWaypoint(re::Point2f(4700, 1000));
            break;
    }
    if (side == Side::DARK)
    {
        waypath.reverse();
    }
    go_to(*waypath.next());
}

void Creep::checkAggro()
{
    for (auto iter : *(units))
    {
        auto unit = std::dynamic_pointer_cast<Unit>(iter);
        if (unit)
        {
            if ((unit->side != side) && (unit->getPosition().distance_to(getPosition()) <= aggroRange))
            {
                std::cout << (side == Side::BRIGHT ? "BRIGHT" : "DARK") << " " << (unit->side == Side::BRIGHT ? "BRIGHT" : "DARK") << std::endl;
                auto attack_event = std::make_shared<AttackEvent>(get_id(), unit->get_id());
                attack_event->set_shared(true);
                re::publish_event( attack_event );
            }
        }
    }
}

void Creep::update(){
    if (cur_action == Action::MOVING)
    {
        if (getPosition().distance_to(goto_point) < 20)
        {
            re::Point2f* next = waypath.next();
            if (next != nullptr)
            {
                go_to(*next);
            } else {
                std::cout << "stop!" << std::endl;
                cur_action = Action::IDLE;
                setVelocity(re::Point2f());
            }
        }
        else
            setVelocity((goto_point - getPosition()).Normalized() * movespeed);
    }
    if(cur_action == Action::ATTACKING)
    {
        re::Point2f enemyPos = dynamic_cast<PhysGameObject*>(GameObject::get_object_by_id(target_id))->getPosition();
        if ((enemyPos - getPosition()).length() > attack_range)
        {
            setVelocity((enemyPos - getPosition()).Normalized() * movespeed);
        } else {
            setVelocity(re::Point2f());
            if ((std::chrono::steady_clock::now() - last_attack_time).count()
                     / 1000000000.0 > 1.0 / (float)attack_per_second)
                attack_event();
        }
    } else {
        checkAggro();
    }
}

void Creep::load_animation() {
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

void Creep::display(re::Camera camera){
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
}

void Creep::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}