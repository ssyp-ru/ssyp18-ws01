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
#include "main_menu.h"

#include "event.h"
#include "events/move_event.h"
#include "events/network_event.h"

#include "gamelogic/gamelogic.h"
#include "gamelogic/lobby.h"

#include "networkmanager.h"

enum class NetworkState {
    menu,
    server,
    client
};

enum class GameState {
    MAIN_MENU,
    LOBBY,
    GAME
};

class MainApp : public re::IBaseApp{
public:
    MainApp()
        : main_menu(gui_manager)
    {}

    NetworkState network_state;

    void setup() override {
        camera.view_at( re::Point2f(0,0) );
        camera.scale( zoom );

        main_menu.setup();

        re::subscribe_to_all(&game_logic);

        player = std::make_shared<Player>(re::Point2f(100, 2200));
        game_logic.world.addObject(player);

        this->network_state = NetworkState::menu;
    }

    void update() override {
        switch (game_state) {
            case GameState::MAIN_MENU: {
                return;
            }
            case GameState::LOBBY: {
                return;
            }
            case GameState::GAME: {
                game_logic.update();
                player->update();
                return;
            }
        }
    }

    void display() override {
        switch (game_state) {
            case GameState::MAIN_MENU: {
                main_menu.display();
                return;
            }
            case GameState::LOBBY: {
                return;
            }
            case GameState::GAME: {
                game_logic.draw(camera);
                player->display(camera);
                return;
            }
        }
    }

    void on_mouse_move( int x, int y ) override {
        cursor_pos.x = x;
        cursor_pos.y = y;
    }

    void on_key_pressed(re::Key key){
        if(game_state == GameState::MAIN_MENU){
            main_menu.on_key_pressed(key);
        }
        
        
        switch( key ) {
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
        }
    }

    void on_button_pressed(int button) override {
        gui_manager.on_click(button, cursor_pos.x, cursor_pos.y);

        if (game_state == GameState::GAME){
            re::Point2f finish_point = camera.screen_to_world(cursor_pos);
            auto move_event = std::make_shared<MoveEvent>(0, finish_point);
            move_event->set_shared(true);
            re::publish_event(move_event);
        }
    }

private:
    GameState game_state = GameState::MAIN_MENU;
    GameLogic game_logic;
    re::Camera camera;
    MainMenu main_menu;
    re::GuiManager gui_manager;

    re::Point2f cursor_pos;
    float zoom = 10;
    int mouseX, mouseY;
    std::shared_ptr<Player> player;

    NetworkManager network_manager;
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 1280, 800, std::make_shared<MainApp>() );
    return 0;
}
