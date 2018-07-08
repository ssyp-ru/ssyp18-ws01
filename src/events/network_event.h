#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int NETWORK_EVENT_CATEGORY = 2;

enum class NetworkEventType {
    CLIENT_CONNECTED,
    CLIENT_DISCONNECTED,
    CONNECT,
    CONNECT_COMPLETE,
    START_SERVER
};

class NetworkConnectionEvent : public re::Event {
public:
    NetworkConnectionEvent(int sock_id)
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::CLIENT_CONNECTED)
        , sock_id(sock_id)
    {}

    std::string get_describe_string() { return "NetworkConnectionEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
    int sock_id;
};

class NetworkDisconnectionEvent : public re::Event {
public:
    NetworkDisconnectionEvent(int sock_id)
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::CLIENT_DISCONNECTED)
        , sock_id(sock_id)
    {}

    std::string get_describe_string() { return "NetworkDisconnectionEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
    int sock_id;
};

class NetworkConnectEvent : public re::Event {
public:
    NetworkConnectEvent( std::string address, int port )
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::CONNECT)
        , address(address)
        , port(port)
    {}

    std::string get_describe_string() { return "NetworkConnectEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
    std::string address;
    int port;
};

class NetworkConnectCompleteEvent : public re::Event {
public:
    NetworkConnectCompleteEvent()
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::CONNECT_COMPLETE)
    {}

    std::string get_describe_string() { return "NetworkConnectCompleteEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
};

class NetworkServerUpEvent : public re::Event {
public:
    NetworkServerUpEvent( int port )
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::START_SERVER)
        , port(port)
    {}

    std::string get_describe_string() { return "NetworkServerUpEvent"; }
    re::Log::LEVEL get_log_level() { return re::Log::LEVEL::DEBUG; };
    int port;
};