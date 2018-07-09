#include <RealEngine/math.h>
#include <RealEngine/graphic.h>

class FlappyBird {
public:
    re::ImagePtr imgptr;
    bool explode = false;
    const int flappy_bird_size = 600;

    void setup();
    void update();
    void display();
    void on_key_pressed(re::Key key);
private:
    std::vector <int> columnsX_;
    std::vector <int> columns_height_;
    int height_;
    int X_;
    int BirdY_;
    int BirdX_;
    int SpeedY_;
    int ColumnsSpeed_;
    int score_;
    int bestscore_;
    int frame_;
    int column_score_;
    int acceler_;
    bool goUP_;
    bool gameover_;

};