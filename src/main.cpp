#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>

#include <iostream>
#include <memory>

#include "map.h"

class MainApp : public re::IBaseApp{
public:
    re::Camera camera;
    Map map;

    void setup() override {
        map = Map( "map.tmx" );
        camera.view_at( re::Point2f(0,0) );
        camera.scale( 1 );
    }

    void update() override {
    }

    void display() override {
    }

    void on_key_pressed(re::Key key){
    }
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 640, 480, std::make_shared<MainApp>() );
    return 0;
}
