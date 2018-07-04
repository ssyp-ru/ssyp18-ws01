#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>

#include <iostream>
#include <memory>

class MainApp : public re::IBaseApp{
public:

    void setup() override {
    }

    void update() override {
        x = (x + 1) % 100;
    }

    void display() override {
        re::background(re::WHITE);
        re::draw_rectangle(x, y, 50, 50, re::RED);
        re::draw_rectangle(200, 200, 50, 50, re::RED);
        re::draw_line( x, 50, 200, 200, re::BLACK );
        re::draw_text( 100, 100, "TEST TEXT", re::BLACK );
    }

    void on_key_pressed(re::Key key){
        std::cout << "Key pressed\n";
        if (key == re::Key::Escape){
            re::exitApp();
        } else if(key == (re::Key)112) {
            //re::graphic::goFullScreen();
        }
    }

private:
    int x = 0;
    int y = 0;
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 640, 480, std::make_shared<MainApp>() );
    return 0;
}
