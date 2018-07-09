#include "RealEngine/physic_core.h"
#include "RealEngine/config_manager.h"
#include "unit.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

Unit::Unit(re::Point2f pos) 
    : PhysGameObject(pos) 
{
    hp = 500;
    maxhp = 500;
    addPoint(re::Point2f(-10, 25));
    addPoint(re::Point2f(-10, 35));
    addPoint(re::Point2f(5, 35));
    addPoint(re::Point2f(5, 25));
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

Unit::Unit(re::Point2f pos, std::vector<std::vector<int>> &new_map) 
    : PhysGameObject(pos) 
{
    hp = 500;
    maxhp = 500;
    map = new_map;
    addPoint(re::Point2f(-10, 25));
    addPoint(re::Point2f(-10, 35));
    addPoint(re::Point2f(5, 35));
    addPoint(re::Point2f(5, 25));
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

    if(way.size() != 0){
        move_unit();
    }
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

    draw_fireball( camera );
}

void Unit::draw_fireball( re::Camera camera ) {
    if( fireball_alive ) {
        re::Point2f target_pos = ((Unit*)GameObject::get_object_by_id(target_id))->getPosition();
        if( cur_action != Action::ATTACKING || 
            (fireball_pos - target_pos).length() < 1 ) {
            fireball_alive = false;
        } else {
            re::Point2f vector = fireball_pos - target_pos;
            vector.normalize();
            fireball_pos -= vector * 10;
            float size = camera.meter_to_screen(10);
            re::draw_rectangle( camera.world_to_screen(fireball_pos),
                                re::Point2f(size,size),
                                re::RED );
        }
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
    fireball_alive = true;
    fireball_pos = this->getPosition();
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
            set_new_way(move_event->finish_point);
        }
    }
    if (event->get_category() == ATTACK_EVENT_CATEGORY && event->get_type() == int(AttackEventType::PLAYER_DEAL_DAMAGE))
    {
        std::shared_ptr<DealDamageEvent> attack_event = std::static_pointer_cast<DealDamageEvent>(event);
        // std::cout << "attack event! " << this->get_id() << " : " << attack_event->player_id << " > " << attack_event->target_id << std::endl;
        dynamic_cast<Unit*>(GameObject::get_object_by_id(attack_event->target_id))->dealDamage(attack_event->damage);
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

void Unit::update_way(){
    for(unsigned int i = 0; i < way.size(); i++){
        way[i] = re::Point2f(way[i].y * 20 + 10, way[i].x * 20 + 10);
    }
}

void Unit::set_new_way(re::Point2f finish){
    std::vector<std::vector<int>> count;
    way = re::a_star(map, 250, int(getPosition().y / 20),  int(getPosition().x / 20),  int(finish.y / 20),
                  int(finish.x / 20), count);
                  update_way();
    index = 0;
}

re::Point2f Unit::get_cell(int index){
    return way[index];
}
unsigned int Unit::get_index(){
    return index;
}

void Unit::update_index(){
    index ++;
}
void Unit::move_unit(){

    re::Point2f next = get_cell(get_index());
    setVelocity((next - this->getPosition()).Normalized() * movespeed);
    if(((abs(next.x - this->getPosition().x) < 10) && (abs(next.y  - this->getPosition().y) < 10)) && 
       (get_index() != way.size())) {
        update_index();
        re::Point2f next = get_cell(get_index());
        setVelocity((next - this->getPosition()).Normalized() * movespeed);
    }

     if(((abs(next.x - this->getPosition().x) < 10) && (abs(next.y - this->getPosition().y) < 10)) && 
       (get_index() == way.size())) {   
        re::Point2f next = get_cell(get_index());
        setVelocity((next - this->getPosition()).Normalized() * 0);
        way.clear();
    }   
}