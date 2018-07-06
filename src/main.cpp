#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>

#include <iostream>
#include <memory>

#include "map.h"
#include "player.h"
#include "events/move_event.h"

class MainApp : public re::IBaseApp{
public:
    re::Game world;
    re::Camera camera;
    Map map;
    re::Point2f cam_pos;
    float zoom = 10;
    std::shared_ptr<Player> player;
    re::ImagePtr img;
    int mouseX, mouseY;

    // MainApp() : player(re::Point2f(20, 20)) {}

    void setup() override {
        map = Map( world, "map.tmx" );
        camera.view_at( re::Point2f(0,0) );
        camera.scale( zoom );

        player = std::make_shared<Player>(re::Point2f(100, 2200));
        world.addObject(player);

    }

    void update() override {
        // world.updateTick();
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
            cam_pos -= re::Point2f( 0,20 );
            camera.view_at( cam_pos );
            break;
        case re::Key::S:
            cam_pos -= re::Point2f( 0,-20 );
            camera.view_at( cam_pos );
            break;
        case re::Key::A:
            cam_pos -= re::Point2f( 20,0 );
            camera.view_at( cam_pos );
            break;
        case re::Key::D:
            cam_pos -= re::Point2f( -20,0 );
            camera.view_at( cam_pos );
            break;
        case re::Key::Q:
            zoom += 0.5;
            camera.scale( zoom );
            break;
        case re::Key::E:
            zoom -= 0.5;
            camera.scale( zoom );
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
