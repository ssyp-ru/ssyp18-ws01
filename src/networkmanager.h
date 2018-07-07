#pragma once

#include <RealEngine/network.h>
#include <RealEngine/event.h>
#include "event.h"

class NetworkManager : public re::EventSubscriber {
public:
    NetworkManager();
    ~NetworkManager() {};
    virtual void on_event(std::shared_ptr<re::Event> event);
private:
    bool connect( std::string address, int port );
    void create_server( int port );

    re::TCPServerPtr tcp_server_;
    re::TCPClientPtr tcp_client_;

    void server_msg_recive(re::TCPServer::Callback_event event, int id, std::vector<char> msg);

    std::shared_ptr<EventSerealizerClient> event_serealizer_client_;
    std::shared_ptr<EventSerealizerServer> event_serealizer_server_;
};