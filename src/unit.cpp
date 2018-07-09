#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include "unit.h"
#include <iostream>

Unit::Unit(re::Point2f pos) 
    : PhysGameObject(pos) 
{
    hp = 500;
    maxhp = 500;

    addPoint(re::Point2f(-30, -30));
    addPoint(re::Point2f(-30, 30));
    addPoint(re::Point2f(30, 30));
    addPoint(re::Point2f(30, -30));
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0);
    setRigidbodySimulated(true);
    setFriction(1.0);
    setBounciness(0.0);

    last_attack_time = std::chrono::steady_clock::now();

    re::subscribe_to_all( this );
}


void Unit::update(){
    if (cur_action == Action::MOVING)
    {
        if (getPosition().distance_to(goto_point) < 20)
            setVelocity(re::Point2f(0,0));
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
    }
}


void Unit::display(re::Camera camera){
    re::Point2f geo_pos(position.x, position.y);
    re::Point2f screen_pos = camera.world_to_screen(geo_pos); 

    float size = camera.meter_to_screen(50);
    re::draw_rectangle(screen_pos - re::Point2f(size,size), re::Point2f(size,size), re::GREEN);

    if (re::ConfigManager::get_property("common/debug_display") == "1"){
        re::Point2f screen_pos = camera.world_to_screen(goto_point);
        re::draw_rectangle(screen_pos, re::Point2f(size, size), re::RED);
    }
}

void Unit::onCollisionStay(re::PhysicObjectPtr to, re::Point2f vec) {

}

void Unit::go_to(re::Point2f finish_point){
    goto_point = finish_point;
    cur_action = Action::MOVING;
}

void Unit::attack(int target_id)
{
    cur_action = Action::ATTACKING;
    this->target_id = target_id;
}

void Unit::attack_event()
{
    last_attack_time = std::chrono::steady_clock::now();
    //dynamic_cast<Unit*>(GameObject::get_object_by_id(target_id))->dealDamage(damage);
    re::publish_event(std::make_shared<DealDamageEvent>(this->get_id(), target_id, damage));
}

void Unit::dealDamage(int damage)
{
    hp -= damage;
    // std::cout << "attack " << this->get_id() << " hp left: " << hp << std::endl;
    if (hp < 0)
    {
        hp = 0;
        onDeath();
    }
}

void Unit::onDeath()
{
    re::publish_event(std::make_shared<DeathEvent>(this->get_id()));
}


void Unit::on_event(std::shared_ptr<re::Event> event) {
    if( event->get_category() == MOVE_EVENT_CATEGORY && event->get_type() == int(MoveEventType::PLAYER_MOVE) ) {
        std::shared_ptr<MoveEvent> move_event = std::static_pointer_cast<MoveEvent>(event);
        if( this->get_id() == move_event->player_id ) {
            go_to(move_event->finish_point);
        }
    }
    if (event->get_category() == ATTACK_EVENT_CATEGORY && event->get_type() == int(AttackEventType::PLAYER_DEAL_DAMAGE))
    {
        std::shared_ptr<DealDamageEvent> attack_event = std::static_pointer_cast<DealDamageEvent>(event);
        //dynamic_cast<Unit*>(GameObject::get_object_by_id(attack_event->target_id))->dealDamage(attack_event->damage);
        GameObject *object = GameObject::get_object_by_id(attack_event->target_id);
        if( object != nullptr ) {
            Unit *target = dynamic_cast<Unit*>( object );
            target->dealDamage(attack_event->damage);
        }
    }
    if (event->get_category() == ATTACK_EVENT_CATEGORY && event->get_type() == int(AttackEventType::PLAYER_DEATH))
    {
        std::shared_ptr<DeathEvent> death_event = std::static_pointer_cast<DeathEvent>(event);
        if (target_id == death_event->player_id){
            target_id = -1;
            cur_action = Action::MOVING;
        }
    }
}