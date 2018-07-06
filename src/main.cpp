#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>

#include <iostream>
#include <memory>

#include "map.h"

class MainApp : public re::IBaseApp{
public:
    re::PhysicWorld world;
    re::Camera camera;
    Map map;
    re::Point2f cam_pos;
    float zoom;

    void setup() override {
        map = Map( world, "map.tmx" );
        camera.view_at( re::Point2f(0,0) );
        camera.scale( 10 );
    }

    void update() override {
    }

    void display() override {
        map.draw(camera);
    }

    void on_key_pressed(re::Key key){
        switch( key )
        {
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
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 640, 480, std::make_shared<MainApp>() );
    return 0;
}
