#pragma once

#include <RealEngine/event.h>
#include <RealEngine/network.h>

void deserealize( std::vector<char> msg );

class EventSerealizerServer : public re::EventSubscriber
{
public:
    EventSerealizerServer( re::TCPServerPtr server );

    virtual void on_event(std::shared_ptr<re::Event> event);
    void deserealize_server( int id, std::vector<char> msg );
private:
    re::TCPServerPtr tcp_server;
};

class EventSerealizerClient : public re::EventSubscriber
{
public:
    EventSerealizerClient( re::TCPClientPtr client );

    virtual void on_event(std::shared_ptr<re::Event> event);
    void deserealize_client( std::vector<char> msg );
private:
    re::TCPClientPtr tcp_client;
};