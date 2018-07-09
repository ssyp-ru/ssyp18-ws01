#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int ATTACK_EVENT_CATEGORY = 11;

enum class AttackEventType {
    PLAYER_ATTACK,
    PLAYER_DEAL_DAMAGE,
    PLAYER_SYNC,
    PLAYER_DEATH
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

    std::string get_describe_string() { return "AttackEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };

    int target_id = 0;
    int player_id = 0;
};

class DealDamageEvent : public re::Event {
public:
    DealDamageEvent(int _player_id, int _target_id, int _damage)
        : Event(ATTACK_EVENT_CATEGORY, (int)AttackEventType::PLAYER_DEAL_DAMAGE)
        , damage(_damage)
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

    std::string get_describe_string() { return "DealDamageEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };

    int damage = 0;
    int target_id = 0;
    int player_id = 0;
};



class DeathEvent : public re::Event {
public:
    DeathEvent(int _player_id)
        : Event(ATTACK_EVENT_CATEGORY, (int)AttackEventType::PLAYER_DEATH)
        , player_id(_player_id)
    {}

    std::vector<char> serialize()
    {
        nlohmann::json j;
        j["category"] = this->get_category();
        j["type"] = this->get_type();
        j["id"] = this->player_id;

        std::string raw_json = j.dump();
        std::vector<char> msg(raw_json.c_str(),raw_json.c_str()+raw_json.size());
        return msg;
    }

    void deserialize( std::vector<char> msg )
    {
        std::string raw_json( msg.data(), msg.size() );

        nlohmann::json j = nlohmann::json::parse(raw_json);
        player_id = j["id"];
    }

    std::string get_describe_string() { return "DeathEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };

    int player_id = 0;
};