#include "networkmanager.h"

#include "events/network_event.h"

NetworkManager::NetworkManager() {
    re::subscribe_to_event_category( this, NETWORK_EVENT_CATEGORY );
}

bool NetworkManager::connect( std::string address, int port ) {
    tcp_client_ = re::TCPClient::create();
    if( !tcp_client_->connect( "127.0.0.1", 11999 ) ) {
        return false;
    }

    event_serealizer_client_ = std::make_shared<EventSerealizerClient>( tcp_client_ );
    re::subscribe_to_all( event_serealizer_client_.get() );
    return true;
}

void NetworkManager::create_server( int port ) {
    tcp_server_ = re::TCPServer::create();
    tcp_server_->setup(11999);

    tcp_server_->set_callback( std::bind( &NetworkManager::server_msg_recive,
                                        this,
                                        std::placeholders::_1,
                                        std::placeholders::_2,
                                        std::placeholders::_3) );

    event_serealizer_server_ = std::make_shared<EventSerealizerServer>(tcp_server_);
    re::subscribe_to_all( event_serealizer_server_.get() );
}

void NetworkManager::on_event(std::shared_ptr<re::Event> event) {
    switch( event->get_category() ) {
    case NETWORK_EVENT_CATEGORY:
        switch( event->get_type() ) {
            case int(NetworkEventType::CONNECT):
            {
                auto connect_event = std::dynamic_pointer_cast<NetworkConnectEvent,re::Event>( event );
                if( this->connect( connect_event->address, connect_event->port ) )
                {
                    auto connect_complete_event = std::make_shared<NetworkConnectCompleteEvent>();
                    re::publish_event( connect_complete_event );
                } else {
                    //int x = 0;
                };
                break;
            }
            case int(NetworkEventType::START_SERVER):
            {
                auto server_up_event = std::dynamic_pointer_cast<NetworkServerUpEvent,re::Event>( event );
                this->create_server( server_up_event->port );
            }
        }
        break;
    }
}

void NetworkManager::server_msg_recive(re::TCPServer::Callback_event event, int id, std::vector<char> msg) {
    switch( event ) {
        case re::TCPServer::Callback_event::connect:
        {
            auto conn_event = std::make_shared<NetworkConnectionEvent>( id );
            conn_event->set_shared(false);
            re::publish_event( conn_event );
            return;
        }
        case re::TCPServer::Callback_event::disconnect:
        {
            auto disconnect_event = std::make_shared<NetworkDisconnectionEvent>( id );
            disconnect_event->set_shared(false);
            re::publish_event( disconnect_event );
            return;
        }
        case re::TCPServer::Callback_event::msg_recive:
        {
            event_serealizer_server_->deserealize_server( id, msg );
            return;
        }       
    }
}