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

enum class Network_state {
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

    Network_state network_state;

    Lobby lobby;

    void setup() override {
        camera.view_at( re::Point2f(0,0) );
        camera.scale( zoom );

        main_menu.setup();

        re::subscribe_to_all(&game_logic);

        player = std::make_shared<Player>(re::Point2f(100, 2200));
        game_logic.world.addObject(player);

        this->network_state = Network_state::menu;
    }

    void server_event_recive(re::TCPServer::Callback_event event, int id, std::vector<char> msg)
    {
        switch( event )
        {
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
                event_serealizer_server->deserealize_server( id, msg );
                return;
            }       
        }
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
            case re::Key::O:
            {
                tcp_client = re::TCPClient::create();
                tcp_client->connect( "127.0.0.1", 11999 );

                event_serealizer_client = std::make_shared<EventSerealizerClient>( tcp_client );
                re::subscribe_to_all( event_serealizer_client.get() );

                this->game_state = GameState::LOBBY;
                this->network_state = Network_state::client;

                re::subscribe_to_event_category( &lobby, LOBBY_EVENT_CATEGORY );

                auto join_event = std::make_shared<LobbyJoinEvent>( std::string( "name" ) + std::to_string(20) );
                join_event->set_shared(true);
                lobby.is_server = false;
                re::publish_event(join_event);
                break;
            }
            case re::Key::P:
            {
                tcp_server = re::TCPServer::create();
                tcp_server->setup(11999);

                tcp_server->set_callback( std::bind( &MainApp::server_event_recive,
                                                    this,
                                                    std::placeholders::_1,
                                                    std::placeholders::_2,
                                                    std::placeholders::_3) );

                event_serealizer_server = std::make_shared<EventSerealizerServer>(tcp_server);
                re::subscribe_to_all( event_serealizer_server.get() );

                this->game_state = GameState::LOBBY;
                this->network_state = Network_state::server;

                lobby.is_server = true;

                re::subscribe_to_event_category( &lobby, NETWORK_EVENT_CATEGORY );
                re::subscribe_to_event_category( &lobby, LOBBY_EVENT_CATEGORY );
                break;
            }
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

    re::TCPClientPtr tcp_client;
    re::TCPServerPtr tcp_server;

    std::shared_ptr<EventSerealizerClient> event_serealizer_client;
    std::shared_ptr<EventSerealizerServer> event_serealizer_server;
};

int main(){
    re::setWindowName( "RealEngine" );
    re::runApp( 1280, 800, std::make_shared<MainApp>() );
    return 0;
}
