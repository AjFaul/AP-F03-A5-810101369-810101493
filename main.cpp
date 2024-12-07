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
const int ARROW_UP=2;
const int ARROW_DOWN=3;
const int KEY_S=4;
const int KEY_W=5;
const int KEY_ENTER=6;
//---------------------


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
            return KEY_S;

        if(event.key.code==Keyboard::W)
            return KEY_W;
        
        if(event.key.code==Keyboard::Up)
            return ARROW_UP;

        if(event.key.code==Keyboard::Down)
            return ARROW_DOWN;

        if(event.key.code==Keyboard::Enter)
            return KEY_ENTER;
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
    Texture textures;
    textures=set_image(ADDRESS_IMG+"Start.png");
    Sprite sprite;
    sprite.setTexture(textures);
    int status_game=START;


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
        

















        

        update_window(window,sprite);
    }
    

}



int main(){
    start_game();
    return 0;
}
