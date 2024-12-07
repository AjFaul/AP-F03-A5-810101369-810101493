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



    while (window.isOpen())
    {
        

        update_window(window,sprite);
    }
    

}



int main(){
    start_game();
    return 0;
}
