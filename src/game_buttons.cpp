#include "game_buttons.h"

GameMenu::GameMenu(re::GuiManager& guiManager) 
    : guiManager_(guiManager)
{}

void GameMenu::skill1(){
}
void GameMenu::skill2(){
}
void GameMenu::skill3(){
}
void GameMenu::skill4(){
}
void GameMenu::set_val(int new_exp, int new_hp, int new_mp){
    exp = new_exp;
    hp = new_hp;
    mp = new_mp;

}

void GameMenu::setup() {
    re::ImagePtr skill1_icon = std::make_shared<re::Image>("1.png");
    skill1_button = std::make_shared<re::BaseButton>(20, 100, "skill1", skill1_icon, skill1_icon);
    skill1_button->register_action(std::bind(&GameMenu::skill1, this));
    guiManager_.register_button(skill1_button, "game_menu");

    re::ImagePtr skill2_icon = std::make_shared<re::Image>("2.png");
    skill2_button = std::make_shared<re::BaseButton>(20, 250, "skill2", skill2_icon, skill2_icon);
    skill2_button->register_action(std::bind(&GameMenu::skill2, this));
    guiManager_.register_button(skill2_button, "game_menu");

    re::ImagePtr skill3_icon = std::make_shared<re::Image>("3.png");
    skill3_button = std::make_shared<re::BaseButton>(20, 400, "skill3", skill3_icon, skill3_icon);
    skill3_button->register_action(std::bind(&GameMenu::skill3, this));
    guiManager_.register_button(skill3_button, "game_menu");

    re::ImagePtr skill4_icon = std::make_shared<re::Image>("4.png");
    skill4_button = std::make_shared<re::BaseButton>(20, 550, "skill4", skill4_icon, skill4_icon);
    skill4_button->register_action(std::bind(&GameMenu::skill4, this));
    guiManager_.register_button(skill4_button, "game_menu");

    guiManager_.layer_set_active("game_menu", true);

}

void GameMenu::display(int mouseX, int mouseY) {
    re::draw_rectangle(0, 700, 1600, 200, re::DARKGREEN);
    guiManager_.display(mouseX, mouseY);  
    re::draw_rectangle(250, 710, exp * 10, 50, re::YELLOW);
    re::draw_rectangle(250, 770, hp * 10, 50, re::RED);
    re::draw_rectangle(250, 830, mp * 10, 50, re::BLUE);
}
