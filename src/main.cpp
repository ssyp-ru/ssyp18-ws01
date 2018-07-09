#include <RealEngine/baseApp.h>
#include <RealEngine/graphic.h>
#include <RealEngine/camera.h>
#include <RealEngine/network.h>
#include <RealEngine/event.h>
#include <RealEngine/config_manager.h>
#include <RealEngine/logger.h>


#include <iostream>
#include <memory>
#include <unistd.h>
#include "event.h"
#include "map.h"
#include "player.h"
#include "main_menu.h"
#include "game_buttons.h"
#include "flappybird.h"

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
    FLAPPY_BIRD,
    GAME
};

const int camera_move_detect_szie = 50;
const int camera_move_speed = 20;

void set_log_level(){
    std::string console_level = re::ConfigManager::get_property("log/console");
    std::string file_level = re::ConfigManager::get_property("log/file");
    std::string screen_level = re::ConfigManager::get_property("log/screen");
    if (console_level == "trace") {
        re::Log::set_console_level(re::Log::LEVEL::TRACE);
    }
    if (console_level == "debug") {
        re::Log::set_console_level(re::Log::LEVEL::DEBUG);
    }
    if (console_level == "info") {
        re::Log::set_console_level(re::Log::LEVEL::INFO);
    }
    if (file_level == "trace") {
        re::Log::set_file_level(re::Log::LEVEL::TRACE);
    }
    if (file_level == "debug") {
        re::Log::set_file_level(re::Log::LEVEL::DEBUG);
    }
    if (file_level == "info") {
        re::Log::set_file_level(re::Log::LEVEL::INFO);
    }
    if (screen_level == "trace") {
        re::Log::set_screen_level(re::Log::LEVEL::TRACE);
    }
    if (screen_level == "debug") {
        re::Log::set_screen_level(re::Log::LEVEL::DEBUG);
    }
    if (screen_level == "info") {
        re::Log::set_screen_level(re::Log::LEVEL::INFO);
    }
}

class MainApp : public re::IBaseApp
              , public re::EventSubscriber
{
public:
    MainApp()
        : main_menu(gui_manager)
        ,  game_menu(gui_manager)
    {
        set_log_level();
        re::subscribe_to_event_type( this, GAME_EVENT_CATEGORY, int(GameEventType::GAME_START) );
    }

    NetworkState network_state;

    void setup() override {
        if (fullscreen)
            re::go_full_screen();

        camera.view_at(re::Point2f(200, 4000));

        camera.scale( zoom );
        
        main_menu.setup();
        
        re::subscribe_to_all(&game_logic);
        flappy_bird.setup();
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

                if( game_state == GameState::GAME ) {
                    if( cursor_pos.y < camera_move_detect_szie ) {
                        camera.translate( re::Point2f( 0, -camera_move_speed ) );
                    } else if( re::get_height() - cursor_pos.y < camera_move_detect_szie ) {
                        camera.translate( re::Point2f( 0, camera_move_speed ) );
                    }
                    if( cursor_pos.x < camera_move_detect_szie ) {
                        camera.translate( re::Point2f( -camera_move_speed, 0 ) );
                    } else if( re::get_width() - cursor_pos.x < camera_move_detect_szie ) {
                        camera.translate( re::Point2f( camera_move_speed, 0 ) );
                    }

                }
                return;
            }
            case GameState::FLAPPY_BIRD: {
                flappy_bird.update();
            }
        }
    }

    void on_event( std::shared_ptr<re::Event> event ) {
        switch( event->get_category() ) {
        case GAME_EVENT_CATEGORY:
            switch( event->get_type() ) {
                case int(GameEventType::GAME_START):
                {
                    gui_manager.layer_set_active("select_side", false);
                    gui_manager.layer_set_active("game_menu", true);
                    game_state = GameState::GAME;
                    break;
                }
            }
            break;
        }
    }

    void display() override {
        switch (game_state) {
            case GameState::MAIN_MENU: {
                main_menu.display(cursor_pos.x, cursor_pos.y );
                return;
            }
            case GameState::LOBBY: {
                return;
            }
            case GameState::FLAPPY_BIRD: {
                flappy_bird.display();
                return;
            }
            case GameState::GAME: {
                
                game_logic.draw(camera);
                game_menu.display(cursor_pos.x, cursor_pos.y);
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
            if( key == re::Key::L ) {
                game_state = GameState::FLAPPY_BIRD;
            }
            main_menu.on_key_pressed(key);
        } else if(game_state == GameState::FLAPPY_BIRD) {
            if( key == re::Key::Escape ) {
                game_state = GameState::MAIN_MENU;
                return;
            }
            flappy_bird.on_key_pressed(key);
        }
        
        
        switch( key ) {
            case re::Key::Escape: re::exitApp();
            case re::Key::W:
                camera.translate( re::Point2f( 0,-20 ) );
                break;
            case re::Key::S:
                camera.translate( re::Point2f( 0,20 ) );
                break;
            case re::Key::A:
                camera.translate( re::Point2f( -20,0 ) );
                break;
            case re::Key::D:
                camera.translate( re::Point2f( 20,0 ) );
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

        if((game_state == GameState::GAME ) && (game_logic.obstacles[int(camera.screen_to_world( cursor_pos ).y  / 20)]
                                                        [int(camera.screen_to_world( cursor_pos ).x  / 20)] == 0)) {

            std::cout << int(cursor_pos.x) << " " << int(cursor_pos.y)   << std::endl;
            game_logic.click( camera.screen_to_world( cursor_pos ) );
        }
    }

private:
    GameState game_state = GameState::MAIN_MENU;
    GameLogic game_logic;
    re::Camera camera;
    MainMenu main_menu;
    GameMenu game_menu;
    re::GuiManager gui_manager;

    re::Point2f cursor_pos;
    float zoom = 1;
    int mouseX, mouseY;
    bool fullscreen = true;

    FlappyBird flappy_bird;

    NetworkManager network_manager;
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 1600, 900, std::make_shared<MainApp>() );
    return 0;
}
