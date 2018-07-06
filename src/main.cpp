#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>
#include <RealEngine/network.h>
#include <RealEngine/event.h>

#include <iostream>
#include <memory>

#include "event.h"
#include "map.h"
#include "player.h"
#include "events/move_event.h"

class MainApp : public re::IBaseApp{
public:
    re::Physic world;
    re::Camera camera;
    Map map;
    re::Point2f cam_pos;
    float zoom = 10;
    std::shared_ptr<Player> player;
    re::ImagePtr img;
    int mouseX, mouseY;

    // MainApp() : player(re::Point2f(20, 20)) {}

    re::TCPClientPtr tcp_client;
    re::TCPServerPtr tcp_server;

    std::shared_ptr<EventSerealizerClient> event_serealizer_client;
    std::shared_ptr<EventSerealizerServer> event_serealizer_server;

    void setup() override {
        map = Map(world, "map.tmx" );
        camera.view_at( re::Point2f(0,0) );
        camera.scale( zoom );

        player = std::make_shared<Player>(re::Point2f(100, 2200));
        world.addObject(player);

    }

    void server_event_recive(re::TCPServer::Callback_event event, int id, std::vector<char> msg)
    {
        event_serealizer_server->deserealize_server( id, msg );
    }

    void update() override {
        //world.updateTick();
        player->update();
    }

    void display() override {
        map.draw(camera);
        player->display(camera);

    }

    void on_key_pressed(re::Key key){
        switch( key )
        {
        case re::Key::Escape: re::exitApp();
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
        }
    }

    void on_button_pressed(int button){
        re::Point2f finish_point = camera.screen_to_world(re::Point2f(mouseX, mouseY));
        auto move_event = std::make_shared<MoveEvent>(0, finish_point);
        re::publish_event(move_event);

    }

    void on_mouse_move(int x, int y){
        mouseX = x;
        mouseY = y;
    }
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 640, 480, std::make_shared<MainApp>() );
    return 0;
}
