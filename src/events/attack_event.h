#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int ATTACK_EVENT_CATEGORY = 6;

enum class AttackEventType {
    PLAYER_ATTACK,
    PLAYER_DEAL_DAMAGE,
    PLAYER_SYNC
};

class AttackEvent : public re::Event {
public:
    AttackEvent(int _player_id, int _target_id)
        : Event(ATTACK_EVENT_CATEGORY, (int)AttackEventType::PLAYER_ATTACK)
        , target_id(_target_id)
        , player_id(_player_id)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        j["target"] = this->target_id;
        j["id"] = this->player_id;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        target_id = j["target"];
        player_id = j["id"];
    }

    int target_id = 0;
    int player_id = 0;
};

class DealDamageEvent : public re::Event {
public:
    DealDamageEvent(int _player_id, int _target_id, int _damage)
        : Event(ATTACK_EVENT_CATEGORY, (int)AttackEventType::PLAYER_DEAL_DAMAGE)
        , target_id(_target_id)
        , player_id(_player_id)
        , damage(_damage)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        j["target"] = this->target_id;
        j["id"] = this->player_id;
        j["damage"] = this->damage;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        target_id = j["target"];
        player_id = j["id"];
        damage = j["damage"];
    }

    int damage = 0;
    int target_id = 0;
    int player_id = 0;
};