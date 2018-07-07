#pragma once

#include "RealEngine/event.h"
#include "RealEngine/math.h"

#include <json.hpp>

const int NETWORK_EVENT_CATEGORY = 2;

enum class NetworkEventType {
    CONNECT,
    DISCONNECT
};

class NetworkConnectionEvent : public re::Event {
public:
    NetworkConnectionEvent(int sock_id)
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::CONNECT)
        , sock_id(sock_id)
    {}
    int sock_id;
};

class NetworkDisconnectionEvent : public re::Event {
public:
    NetworkDisconnectionEvent(int sock_id)
        : Event(NETWORK_EVENT_CATEGORY, (int)NetworkEventType::DISCONNECT)
        , sock_id(sock_id)
    {}
    int sock_id;
};