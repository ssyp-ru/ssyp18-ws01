#include "main_menu.h"

MainMenu::MainMenu(re::GuiManager& guiManager) 
    : guiManager_(guiManager)
{}

void MainMenu::setup() {
    menuBackground = std::make_shared<re::Image>("menu.png");
    players = std::make_shared<re::Image>("players.png");




    re::ImagePtr join_icon = std::make_shared<re::Image>("join.png");
    join_game_button_ = std::make_shared<re::BaseButton>(20, 220, "join", join_icon, join_icon);
    join_game_button_->register_action(std::bind(&MainMenu::join_name, this));
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


    re::ImagePtr choose_dark_button__icon = std::make_shared<re::Image>("dark.png");
    choose_dark_button_ = std::make_shared<re::BaseButton>(20, 760, "dark", choose_dark_button__icon, choose_dark_button__icon);
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

void MainMenu::display() {
    re::draw_image(0, 0, menuBackground);
    guiManager_.display(mouseX, mouseY);  
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
