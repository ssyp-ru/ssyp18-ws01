#include "game_buttons.h"


GameMenu::GameMenu(re::GuiManager& guiManager, GameLogic& gameLogic) 
    : guiManager_(guiManager)
    , game_logic(gameLogic)
{}

void GameMenu::skill1(){
}
void GameMenu::skill2(){
}
void GameMenu::skill3(){
}
void GameMenu::skill4(){
}
void GameMenu::set_hp(int new_hp){
    hp = new_hp;
}

void GameMenu::setup() {
}

void GameMenu::display(int mouseX, int mouseY) {
    re::ImagePtr hud = std::make_shared<re::Image>("screen_panel.png");
    re::draw_image(0, 711, hud);
    guiManager_.display(mouseX, mouseY); 
    set_hp(get_player(lobby.get_self_id()).);
    re::draw_rectangle(294, 732, exp * 7 + 6, 40, re::Color(198, 182, 29));
    re::draw_rectangle(294, 786, hp * 7 + 6, 41, re::Color(177, 33, 7));
    re::draw_rectangle(293, 842, mp * 7 + 6, 40, re::Color(3, 31, 177));
}
