#include "main_menu.h"

MainMenu::MainMenu(re::GuiManager& guiManager) 
    : guiManager_(guiManager)
{}

void MainMenu::join_game(){
    connect_button_->set_active(true);
    join_game_button_->set_active(false);
    empty_ip_button_->set_active(true);
    menu_state = MenuState::IP_INPUT;
}

void MainMenu::create_game(){

    auto server_up_event = std::make_shared<NetworkServerUpEvent>( 11999 );
    re::publish_event( server_up_event );

    LobbyMember owner;
    owner.name = nick;
    owner.team = 0;
    
    lobby.join( owner );

    guiManager_.layer_set_active("main_menu", false);
    guiManager_.layer_set_active("select_side", true);
}

void MainMenu::exit_game(){
    re::exitApp();
}

void MainMenu::set_nick(){
    change_nick_button_->set_active(true);
    menu_state = MenuState::NICK_INPUT;
}
void MainMenu::set_ip(){
}

void MainMenu::change_nick(){
    change_nick_button_->set_active(false);
    menu_state = MenuState::MAIN_MENU;
}

void MainMenu::connect(){
    connect_button_->set_active(false);
    empty_ip_button_->set_active(false);
    join_game_button_->set_active(true);
    menu_state = MenuState::MAIN_MENU;
    guiManager_.layer_set_active("main_menu", false);
    guiManager_.layer_set_active("select_side", true);

    auto connect_event = std::make_shared<NetworkConnectEvent>( ip, 11999 );
    re::publish_event( connect_event );
    go_button_->set_active(false);
}

void MainMenu::go(){
    auto start_event = std::make_shared<GameStartEvent>();
    start_event->set_shared(true);
    re::publish_event( start_event );
}


void MainMenu::choose_dark(){
    auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( nick, 1 , lobby.get_self_id() );
    lobby_switch_event->set_shared(true);
    re::publish_event( lobby_switch_event );
}

void MainMenu::choose_bright(){
    auto lobby_switch_event = std::make_shared<LobbyJoinEvent>( nick, 0, lobby.get_self_id()  );
    lobby_switch_event->set_shared(true);
    re::publish_event( lobby_switch_event );
}
 




void MainMenu::setup() {
    menuBackground = std::make_shared<re::Image>("menu.png");
    players = std::make_shared<re::Image>("players.png");

    re::ImagePtr join_icon = std::make_shared<re::Image>("join.png");
    join_game_button_ = std::make_shared<re::BaseButton>(20, 220, "join", join_icon, join_icon);
    join_game_button_->register_action(std::bind(&MainMenu::join_game, this));
    guiManager_.register_button(join_game_button_, "main_menu");

    re::ImagePtr create_icon = std::make_shared<re::Image>("create.png");
    create_game_button_ = std::make_shared<re::BaseButton>(20, 520, "create", create_icon, create_icon);
    create_game_button_->register_action(std::bind(&MainMenu::create_game, this));
    guiManager_.register_button(create_game_button_, "main_menu");

    re::ImagePtr exit_icon = std::make_shared<re::Image>("exit.png");
    exit_game_button_ = std::make_shared<re::BaseButton>(20, 720, "exit", exit_icon, exit_icon);
    exit_game_button_->register_action(std::bind(&MainMenu::exit_game, this));
    guiManager_.register_button(exit_game_button_, "main_menu");

    re::ImagePtr empty_nick_icon = std::make_shared<re::Image>("empty.png");
    empty_nick_button_ = std::make_shared<re::BaseButton>(20, 20, "empty", empty_nick_icon, empty_nick_icon);
    empty_nick_button_->register_action(std::bind(&MainMenu::set_nick, this));
    guiManager_.register_button(empty_nick_button_, "main_menu");

    re::ImagePtr change_icon = std::make_shared<re::Image>("change.png");
    change_nick_button_ = std::make_shared<re::BaseButton>(20, 120, "change", change_icon, change_icon);
    change_nick_button_->register_action(std::bind(&MainMenu::change_nick, this));
    guiManager_.register_button(change_nick_button_, "main_menu");
    change_nick_button_->set_active(false);
    

    re::ImagePtr connect_icon = std::make_shared<re::Image>("connect.png");
    connect_button_ = std::make_shared<re::BaseButton>(20, 320, "connect", connect_icon, connect_icon);
    connect_button_->register_action(std::bind(&MainMenu::connect, this));
    guiManager_.register_button(connect_button_, "main_menu");
    connect_button_->set_active(false);

    re::ImagePtr ip_icon = std::make_shared<re::Image>("empty.png");
    empty_ip_button_ = std::make_shared<re::BaseButton>(20, 220, "ip", ip_icon, ip_icon);
    empty_ip_button_->register_action(std::bind(&MainMenu::set_ip, this));
    guiManager_.register_button(empty_ip_button_, "main_menu");
    empty_ip_button_->set_active(false);


    re::ImagePtr dark_icon = std::make_shared<re::Image>("dark.png");
    choose_dark_button_ = std::make_shared<re::BaseButton>(20, 760, "dark",dark_icon, dark_icon);
    choose_dark_button_->register_action(std::bind(&MainMenu::choose_dark, this));
    guiManager_.register_button(choose_dark_button_, "select_side");


    re::ImagePtr bright_icon = std::make_shared<re::Image>("bright.png");
    choose_bright_button_ = std::make_shared<re::BaseButton>(20, 360, "bright", bright_icon, bright_icon);
    choose_bright_button_->register_action(std::bind(&MainMenu::choose_bright, this));
    guiManager_.register_button(choose_bright_button_, "select_side");


    re::ImagePtr go_icon = std::make_shared<re::Image>("go.png");
    go_button_ = std::make_shared<re::BaseButton>(420, 360, "go", go_icon, go_icon);
    go_button_->register_action(std::bind(&MainMenu::go, this));
    guiManager_.register_button(go_button_, "select_side");

    guiManager_.layer_set_active("select_side", false);

}

void MainMenu::on_event( std::shared_ptr<re::Event> event )
{
    if( event->get_category() == NETWORK_EVENT_CATEGORY &&
        event->get_type() == int(NetworkEventType::CONNECT_COMPLETE) )
    {
        connect_button_->set_active(false);
        empty_ip_button_->set_active(false);
        join_game_button_->set_active(true);
        menu_state = MenuState::MAIN_MENU;
        guiManager_.layer_set_active("main_menu", false);
        guiManager_.layer_set_active("select_side", true);
    }
}    

void MainMenu::display() {
    re::draw_image(0, 0, menuBackground);
    guiManager_.display(mouseX, mouseY); 
    re::draw_text_custom(empty_nick_button_->get_pos().x + 10, empty_nick_button_->get_pos().y + 30, 6, nick, re::GRAY); 
    if(empty_ip_button_->is_active()){
        re::draw_text_custom(empty_ip_button_->get_pos().x + 10, empty_ip_button_->get_pos().y + 30, 6, ip, re::GRAY);
    }
    if(choose_dark_button_->is_active()){
        re::draw_image(20, 20, players);
        re::draw_image(20, 420, players);

        int team_a_count = 0;
        int team_b_count = 0;

        for( int i = 0; i < lobby.get_players_count(); i++ ) {
            switch( int(lobby.get_player(i).team) ) {
                case 0:
                    re::draw_text( 40, 50 + (team_a_count * 30), lobby.get_player(i).name, re::WHITE );
                    team_a_count++;
                    break;
                case 1:
                    re::draw_text( 40, 450 + (team_b_count * 30), lobby.get_player(i).name, re::BLACK );
                    team_b_count++;
                    break;
            }
        }
    }

}
void MainMenu::on_key_pressed(re::Key key){
    if(menu_state == MenuState::IP_INPUT && ((int)key >= (int)re::Key::Num0 && (int)key <= (int)re::Key::Num9)){
        char key_val = (int)key + (int)'0' - (int)re::Key::Num0;
        ip += key_val;
    }
    if(menu_state == MenuState::IP_INPUT && (int)key == (int)re::Key::P){
        ip += '.';
    }
    if(menu_state == MenuState::IP_INPUT && (int)key == (int)re::Key::BackSpace && ip.size() > 0){
        ip.pop_back();
    }

    if(menu_state == MenuState::NICK_INPUT && ((int)key >= (int)re::Key::A && (int)key <= (int)re::Key::Z)){
        char key_val = (int)key + (int)'A' - (int)re::Key::A;
        nick += key_val;
    }
    if(menu_state == MenuState::NICK_INPUT && (int)key == (int)re::Key::BackSpace && nick.size() > 0){
        nick.pop_back();
    }
}
