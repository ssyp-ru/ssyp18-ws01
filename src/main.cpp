#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>
#include <RealEngine/network.h>
#include <RealEngine/event.h>

#include <iostream>
#include <memory>

#include "map.h"
#include "event.h"

#include "events/event_input.h"
#include "events/event_enum.h"

#include "gamelogic/gamelogic.h"

class MainApp : public re::IBaseApp{
public:
    GameLogic game_logic;
    re::Camera camera;
    re::Point2f cam_pos;
    re::Point2f cursor_pos;
    float zoom;

    re::TCPClientPtr tcp_client;
    re::TCPServerPtr tcp_server;

    std::shared_ptr<EventSerealizerClient> event_serealizer_client;
    std::shared_ptr<EventSerealizerServer> event_serealizer_server;

    void setup() override {
        game_logic.map = Map( game_logic.world, "map.tmx" );
        camera.view_at( re::Point2f(0,0) );
        camera.scale( 10 );
        re::subscribe_to_all( (&game_logic) );
    } 

    void server_event_recive(re::TCPServer::Callback_event event, int id, std::vector<char> msg)
    {
        if( event == re::TCPServer::Callback_event::msg_recive )
        {
            event_serealizer_server->deserealize_server( id, msg );
        }
    }

    void update() override {
    }

    void display() override {
        game_logic.map.draw(camera);
    }

    void on_mouse_move( int x, int y )
    {
        cursor_pos.x = x;
        cursor_pos.y = y;
    }

    void on_button_pressed( int button )
    {
        std::shared_ptr<InputEventMouse> event = std::make_shared<InputEventMouse>( 
                                        event_category::input ,
                                        event_input::mouse );
        event->button = 1;
        event->pos = camera.screen_to_world( this->cursor_pos );
        event->set_shared( true );
        re::publish_event( event );
    }

    void on_key_pressed(re::Key key){
        switch( key )
        {
        case re::Key::W:
            //camera.translate( re::Point2f( 0,-20 ) );
            break;
        case re::Key::S:
            //camera.translate( re::Point2f( 0,20 ) );
            break;
        case re::Key::A:
            //camera.translate( re::Point2f( -20,0 ) );
            break;
        case re::Key::D:
            //camera.translate( re::Point2f( 20,0 ) );
            break;
        case re::Key::Q:
            zoom += 0.5;
            camera.scale( zoom );
            break;
        case re::Key::E:
            zoom -= 0.5;
            camera.scale( zoom );
            break;
        case re::Key::O:
            tcp_client = re::TCPClient::create();
            tcp_client->connect( "127.0.0.1", 11999 );

            event_serealizer_client = std::make_shared<EventSerealizerClient>( tcp_client );
            re::subscribe_to_all( event_serealizer_client.get() );
            break;
        case re::Key::P:
            tcp_server = re::TCPServer::create();
            tcp_server->setup(11999);

            tcp_server->set_callback( std::bind( &MainApp::server_event_recive,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2,
                                                std::placeholders::_3) );

            event_serealizer_server = std::make_shared<EventSerealizerServer>(tcp_server);
            re::subscribe_to_all( event_serealizer_server.get() );
            break;
        }
    }
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 640, 480, std::make_shared<MainApp>() );
    return 0;
}
