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
//---------------------
const int STOP_TIME_FIRST_GAME=2;
//---------------------
const int LEFT_ARROW=0;
const int RIGHT_ARROW=1;



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
            return ARROW_DOWN_S;

        if(event.key.code==Keyboard::W)
            return ARROW_UP_OR_W;
        
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


            

















            window.display();
        }
        
















        

        update_window(window,sprite);
    }
    

}



int main(){
    start_game();
    return 0;
}
