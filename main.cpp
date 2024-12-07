#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm> 

using namespace std;
using namespace sf;


//---------------------
const int X_PAGE=1024;
const int Y_PAGE=1024;
//---------------------
const string ADDRESS_IMG = "../img/";
//---------------------
const int START=1;
const int INITIAL_TIME=2;
const int IN_GAME=3;
//---------------------
const int CLOSE=0;
const int MOUSE_LEFT=1;
const int ARROW_UP_OR_W=2;
const int ARROW_DOWN_S=3;
const int KEY_ENTER_OR_SPACE=4;


const int UP=5;
const int DOWN=6;
//---------------------
const int STOP_TIME_FIRST_GAME=2;
//---------------------
const int LEFT_ARROW=0;
const int RIGHT_ARROW=1;


class Player
{
private:
    int health;
    string name ;
public:
    Player(string name_player){
        name=name_player;
        health=100;
    }

    ~Player(){}

    int get_health(){return health;}

    int type_health(){
        if(health<=25)
            return 4;
        else if( health<=50)
            return 3;
        else if(health <=75)
            return 2;
        else
            return 1;
    }
};








class Arrow
{
private:
    float x,y;
public:
    Arrow(int type){
        if(type==LEFT_ARROW)
            x=30;
        if(type==RIGHT_ARROW)
            x=915;
        y=212;
    }

    float event_handling(int type_op){
        switch (type_op)
        {
        case ARROW_UP_OR_W:
            y-=212;
            if(y<=150)
                y=828;
            return 0;
        case ARROW_DOWN_S:
            y+=212;
            if(y>=900)
                y=212;
            return 0;
        case KEY_ENTER_OR_SPACE:
            return y;
        default:
            return 0;
        }
    }

    float get_pos_x(){return x;}

    float get_pos_y(){return y;}
    ~Arrow(){}
};







int checkMouseInRectangle_start(sf::RenderWindow &window) {
    FloatRect targetRect(193,202,(709-193),(363-202));
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (targetRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 1;
    }
    return 0;
}

int checkMouseInRectangle_exit(sf::RenderWindow &window) {
    FloatRect targetRect(355,376,(632-355),(482-376));
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (targetRect.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        return 1;
    }
    return 0;
}

int handle_event(const Event & event){
    if(event.type==sf::Event::Closed)
        return 0;
    
    if(event.type==sf::Event::MouseButtonPressed)
        if(event.mouseButton.button==Mouse::Left)
            return 1;

    if(event.type==Event::KeyPressed)
    {
        if(event.key.code==Keyboard::S)
            return DOWN;

        if(event.key.code==Keyboard::W)
            return UP;
        
        if(event.key.code==Keyboard::Up)
            return ARROW_UP_OR_W;

        if(event.key.code==Keyboard::Down)
            return ARROW_DOWN_S;

        if(event.key.code==Keyboard::Enter)
            return KEY_ENTER_OR_SPACE;
    }
    return -1;
}

sf::Texture set_image(string filepath)
{
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(filepath)) 
    {
        cout<<"-1";
    }
    return backgroundTexture;
}

void update_window(sf::RenderWindow & window, Sprite sprites){
    window.clear(sf::Color::Black);
    window.draw(sprites);
    window.display();
}


void update_sprite(Sprite& sprite,float x, float y){
    sprite.setPosition(x,y);
}



void start_game()
{
    RenderWindow window(VideoMode(X_PAGE,Y_PAGE),"Animal Figth");

    //------------------------------------------------------

    Texture textures;
    textures=set_image(ADDRESS_IMG+"Start.png");
    Sprite sprite;
    sprite.setTexture(textures);

    Texture logo_arrow_left;
    logo_arrow_left=set_image(ADDRESS_IMG+"small_yang.png");
    Sprite arrow_left_sprite(logo_arrow_left);

    Texture logo_arrow_right;
    logo_arrow_right=set_image(ADDRESS_IMG+"small_yang.png");
    Sprite arrow_right_sprite(logo_arrow_right);
//-------------------
    Texture logo_health1;
    logo_health1=set_image(ADDRESS_IMG+"health1.png");
    Sprite health1_sprite(logo_health1);

    Texture logo_health2;
    logo_health2=set_image(ADDRESS_IMG+"health2.png");
    Sprite health2_sprite(logo_health2);

    Texture logo_health3;
    logo_health3=set_image(ADDRESS_IMG+"health3.png");
    Sprite health3_sprite(logo_health3);

    Texture logo_health4;
    logo_health4=set_image(ADDRESS_IMG+"health4.png");
    Sprite health4_sprite(logo_health4);

    vector<Sprite> health_sprite={health1_sprite,health2_sprite,health3_sprite,health4_sprite};
//--------------------
//--------------------
    Texture flip_logo_health1;
    flip_logo_health1=set_image(ADDRESS_IMG+"flip_health1.png");
    Sprite flip_health1_sprite(flip_logo_health1);
    flip_health1_sprite.setPosition(800.f,5.f);

    Texture flip_logo_health2;
    flip_logo_health2=set_image(ADDRESS_IMG+"flip_health2.png");
    Sprite flip_health2_sprite(flip_logo_health2);
    flip_health2_sprite.setPosition(800.f,5.f);

    Texture flip_logo_health3;
    flip_logo_health3=set_image(ADDRESS_IMG+"flip_health3.png");
    Sprite flip_health3_sprite(flip_logo_health3);
    flip_health3_sprite.setPosition(800.f,5.f);

    Texture flip_logo_health4;
    flip_logo_health4=set_image(ADDRESS_IMG+"flip_health4.png");
    Sprite flip_health4_sprite(flip_logo_health4);
    flip_health4_sprite.setPosition(800.f,5.f);


    vector<Sprite> flip_health_sprite={flip_health1_sprite,flip_health2_sprite,flip_health3_sprite,flip_health4_sprite};
    //------------------------------------------------------

    int status_game=START;
    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event) && status_game==START)
        {
            if(handle_event(event)==CLOSE)
                window.close();
            if(checkMouseInRectangle_start(window))
                if(handle_event(event)==MOUSE_LEFT)
                {
                    status_game=INITIAL_TIME;
                    break;
                }
            if(checkMouseInRectangle_exit(window) && status_game!=INITIAL_TIME)
                if(handle_event(event)==MOUSE_LEFT)
                    window.close();          
        }

        clock.restart();
        int initial_times=STOP_TIME_FIRST_GAME;
        while (status_game==INITIAL_TIME)
        {
            window.pollEvent(event);
            if(handle_event(event)==CLOSE)
            {
                window.close();
                abort();
            }

            if(clock.getElapsedTime().asSeconds()>=1.0f){
                clock.restart();
                textures=set_image(ADDRESS_IMG+to_string(initial_times)+".png");
                sprite.setTexture(textures);
                initial_times--;
            }
            if(initial_times==0)
                status_game=IN_GAME;
            update_window(window,sprite);
        }
        


        //----------------
        Arrow arr_left(LEFT_ARROW);
        arrow_left_sprite.setPosition(arr_left.get_pos_x(),arr_left.event_handling(KEY_ENTER_OR_SPACE));
        //----------------
        Arrow arr_right(RIGHT_ARROW);
        arrow_right_sprite.setPosition(arr_right.get_pos_x(),arr_right.event_handling(KEY_ENTER_OR_SPACE));
        //----------------
        Player amirabas("amirabas");
        Player ali("ali");
        //----------------
        //----------------
        while (status_game==IN_GAME)
        {
            window.pollEvent(event);

            textures=set_image(ADDRESS_IMG+"background.png");
            sprite.setTexture(textures);
            window.clear(Color::Black);



            window.draw(sprite);
            window.draw(arrow_left_sprite);
            window.draw(arrow_right_sprite);
            if(handle_event(event)==CLOSE)
            {
                window.close();
                abort();
            }

            if(handle_event(event)==DOWN)
                arr_left.event_handling(ARROW_DOWN_S);

            if(handle_event(event)==ARROW_DOWN_S)
                arr_right.event_handling(ARROW_DOWN_S);

            if(handle_event(event)==UP)
                arr_left.event_handling(ARROW_UP_OR_W);
            
            if(handle_event(event)==ARROW_UP_OR_W)
                arr_right.event_handling(ARROW_UP_OR_W);
            
            update_sprite(arrow_left_sprite,arr_left.get_pos_x(),arr_left.get_pos_y());
            update_sprite(arrow_right_sprite,arr_right.get_pos_x(),arr_right.get_pos_y());


            












            window.draw(health_sprite[amirabas.type_health() -1]);
            window.draw(flip_health_sprite[ali.type_health() -1]);

            window.display();
        }
        
















        

        update_window(window,sprite);
    }
    

}



int main(){
    start_game();
    return 0;
}
